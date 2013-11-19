// Copyright [2013] Alexander Rush

#ifndef HYPERGRAPH_SEMIRING_H_
#define HYPERGRAPH_SEMIRING_H_

#include <algorithm>
#include "Hypergraph/Factory.h"
#include "Hypergraph/Hypergraph.h"
#include "./common.h"


class StaticViterbiPotential {
public:
	typedef double ValType;
	static inline ValType add(ValType lhs, const ValType &rhs) {
		lhs = std::max(lhs, rhs);
		return normalize(lhs);
	}

	static inline ValType times(ValType lhs, const ValType &rhs) {
		lhs *= rhs;
		return normalize(lhs);
	}

	static inline ValType& normalize(ValType& val) {
		if (val < 0.0) val = 0.0;
		else if (val > 1.0) val = 1.0;
		return val;
	}

	static inline ValType zero() { return 0.0; }
	static inline ValType one() { return 1.0; }

	static inline ValType randValue() {
		return dRand(0.0,1.0);
	}
};

class StaticLogViterbiPotential : public StaticViterbiPotential {
public:
	static inline ValType times(ValType lhs, const ValType &rhs) {
		lhs += rhs;
		return normalize(lhs);
	}

	static inline ValType zero() { return -INF; }
	static inline ValType one() { return 0.0; }

	static inline ValType& normalize(ValType& val) {
		return val = val < -INF ? -INF : val;
	}

	static inline ValType randValue() {
		return dRand(-INF, 0.0);
	}
};

class StaticInsidePotential : public StaticViterbiPotential {
public:
	static inline ValType add(ValType lhs, const ValType &rhs) {
		lhs += rhs;
		return normalize(lhs);
	}

	static inline ValType times(ValType lhs, const ValType &rhs) {
		lhs *= rhs;
		return normalize(lhs);
	}

	static inline ValType& normalize(ValType& val) {
		return val = val < 0.0 ? 0.0 : val;
	}
};

class StaticRealPotential : public StaticViterbiPotential {
public:
	static inline ValType add(ValType lhs, const ValType &rhs) {
		lhs = std::min(lhs, rhs);
		return normalize(lhs);
	}

	static inline ValType times(ValType lhs, const ValType &rhs) {
		lhs += rhs;
		return normalize(lhs);
	}

	static inline ValType zero() { return INF; }
	static inline ValType one() { return 0.0; }

	static inline ValType& normalize(ValType& val) {
		return val = val > INF ? INF : val;
	}

	static ValType randValue() { return dRand(0.0, INF); }
};

class StaticTropicalPotential : public StaticRealPotential {
public:
	static inline ValType& normalize(ValType& val) {
		if (val < 0.0) val = 0.0;
		else if (val > INF) val = INF;
		return val;
	}
};

class StaticBoolPotential {
public:
	typedef bool ValType;
	static inline ValType add(const ValType& lhs, const ValType &rhs) {
		return lhs || rhs;
	}
	static inline ValType times(const ValType& lhs, const ValType &rhs) {
		return lhs && rhs;
	}

	static inline ValType& normalize(ValType& val) {
		return val;
	}

	static inline ValType one() { return true; }
	static inline ValType zero() { return false; }

	static inline ValType randValue() { return dRand(0.0,1.0) > .5; }
};

class StaticCountingPotential {
public:
	typedef int ValType;
	static inline ValType add(ValType lhs, const ValType &rhs) {
		lhs += rhs;
		return normalize(lhs);
	}

	static inline ValType times(ValType lhs, const ValType &rhs) {
		lhs *= rhs;
		return normalize(lhs);
	}

	static inline ValType& normalize(ValType& val) {
		return val = val < 0 ? 0 : val;
	}

	static inline ValType one() { return 1; }
	static inline ValType zero() { return 0; }

	static inline ValType randValue() {
		return rand();
	}
};


/**
 * An untemplated base class for use in registering types
 */
class BaseSemiring {
public:
	BaseSemiring() : value(zero().value) {}
	BaseSemiring(double val) : value(val) {}
	virtual ~BaseSemiring() { };
	static BaseSemiring one() { return BaseSemiring(1.0); }
	static BaseSemiring zero() { return BaseSemiring(0.0); }
	BaseSemiring identity() { return this->one(); }
	BaseSemiring annihlator() { return this->zero(); }

	inline BaseSemiring& operator+=(const BaseSemiring& rhs) {
		value = value + rhs.value;
		return *this;
	}
	inline BaseSemiring& operator*=(const BaseSemiring& rhs) {
		value = value * rhs.value;
		return *this;
	}

	friend inline bool operator==(const BaseSemiring& lhs, const BaseSemiring& rhs) {
	    return lhs.value == rhs.value;
	}

	friend inline BaseSemiring operator+(BaseSemiring lhs, const BaseSemiring &rhs) {
	    lhs += rhs;
	    return lhs;
	}

	friend BaseSemiring operator*(BaseSemiring lhs, const BaseSemiring &rhs);
protected:
	double value;
};


/**
 * A templated base class of a potential with traits of a semiring
 * including + and * operators, and annihlator/identity elements.
 */
template<typename ValType, typename SemiringPotential>
class BaseSemiringPotential : public BaseSemiring {
public:
	BaseSemiringPotential(const SemiringPotential& other)
		: value(other.value) {}
	BaseSemiringPotential(ValType val) : value(normalize(val)) {}
	BaseSemiringPotential() : value(zero()) {}

	inline operator ValType() const { return value; }

	inline SemiringPotential& operator=(SemiringPotential rhs) {
		normalize(rhs.value);
		std::swap(value, rhs.value);
		return *this;
	}

	inline SemiringPotential& operator=(ValType rhs) {
		normalize(rhs);
		std::swap(value, rhs);
		return *this;
	}

	static SemiringPotential add(SemiringPotential lhs, const SemiringPotential &rhs) {
		return lhs += rhs;
	}

	static SemiringPotential times(SemiringPotential lhs, const SemiringPotential &rhs) {
		return lhs *= rhs;
	}

	friend inline bool operator==(const SemiringPotential& lhs,const SemiringPotential& rhs) {
		return lhs.value == rhs.value;
	}

	friend inline SemiringPotential operator+(SemiringPotential lhs, const SemiringPotential &rhs) {
		lhs += rhs;
		return lhs;
	}
	friend inline SemiringPotential operator*(SemiringPotential lhs, const SemiringPotential &rhs) {
		lhs *= rhs;
		return lhs;
	}

	inline SemiringPotential& operator+=(const SemiringPotential& rhs) {
		value = value + rhs.value;
		return *this;
	}
	inline SemiringPotential& operator*=(const SemiringPotential& rhs) {
		value = value * rhs.value;
		return *this;
	}

	static SemiringPotential one() { return SemiringPotential(1.0); }
	static SemiringPotential zero() { return SemiringPotential(0.0); }
	static ValType randValue() { return dRand(zero(), one()); }

	// Determines range of acceptable values
	ValType& normalize(ValType& val) { return val; }

protected:
	ValType value;
};

/**
 * Implements the Viterbi type of semiring as described in Huang 2006.
 * +: max
 * *: *
 * 0: 0
 * 1: 1
 */
class ViterbiPotential : public BaseSemiringPotential<double, ViterbiPotential> {
public:
	ViterbiPotential(double value) : BaseSemiringPotential<double, ViterbiPotential>(normalize(value)) { }
	ViterbiPotential() : BaseSemiringPotential<double, ViterbiPotential>() { }

	inline ViterbiPotential& operator+=(const ViterbiPotential& rhs) {
		value = std::max(value, rhs.value);
		// std::cout << "vit add" << std::endl;
		return *this;
	}
	inline ViterbiPotential& operator*=(const ViterbiPotential& rhs) {
		value = value * rhs.value;
		// std::cout << "vit times" << std::endl;
		return *this;
	}

	double& normalize(double& val) {
		// std::cout << "vit norm" << std::endl;
		if (val < 0.0) val = 0.0;
		else if (val > 1.0) val = 1.0;
		return val;
	}

	static ViterbiPotential one() { 
		// std::cout << "vit noe" << std::endl;
		return ViterbiPotential(1.0); }
	static ViterbiPotential zero() { 
		// std::cout << "vit zero" << std::endl;
		return ViterbiPotential(0.0); }

// protected:
	BASE_SEMIRING_REGISTRY_DECLARATION(ViterbiPotential);
};


/**
 * Implements the log-space Viterbi type of semiring.
 * +: max
 * *: +
 * 0: -INF
 * 1: 0
 */
class LogViterbiPotential : public BaseSemiringPotential<double, LogViterbiPotential> {
public:
	LogViterbiPotential(double value) :
		BaseSemiringPotential<double, LogViterbiPotential>(normalize(value)) { }
	LogViterbiPotential() :
		BaseSemiringPotential<double, LogViterbiPotential>(LogViterbiPotential::zero()) {}

	inline LogViterbiPotential& operator+=(const LogViterbiPotential& rhs) {
		value = std::max(value, rhs.value);
		return *this;
	}
	inline LogViterbiPotential& operator*=(const LogViterbiPotential& rhs) {
		value = value + rhs.value;
		return *this;
	}

	double& normalize(double& val) {
		return val = val < -INF ? -INF : val;
	}

	static LogViterbiPotential one() { return LogViterbiPotential(0.0); }
	static LogViterbiPotential zero() { return LogViterbiPotential(-INF); }


// protected:
	BASE_SEMIRING_REGISTRY_DECLARATION(LogViterbiPotential);
};


/**
 * Implements the Boolean type of semiring as described in Huang 2006
 * +: logical or
 * *: logical and
 * 0: false
 * 1: true
 */
class BoolPotential : public BaseSemiringPotential<bool, BoolPotential> {
public:
	BoolPotential(bool value) : BaseSemiringPotential<bool, BoolPotential>(normalize(value)) { }
	BoolPotential() : BaseSemiringPotential<bool, BoolPotential>() { }

	inline BoolPotential& operator+=(const BoolPotential& rhs) {
		value = value || rhs.value;
		return *this;
	}
	inline BoolPotential& operator*=(const BoolPotential& rhs) {
		value = value && rhs.value;
		return *this;
	}

	static BoolPotential one() { return BoolPotential(true); }
	static BoolPotential zero() { return BoolPotential(false); }
	static bool randValue() { return rand()/RAND_MAX > .5 ? true : false; }


// protected:
	BASE_SEMIRING_REGISTRY_DECLARATION(BoolPotential);
};

/**
 * Implements the Inside type of semiring as described in Huang 2006
 * +: +
 * *: *
 * 0: 0
 * 1: 1
 */
class InsidePotential : public BaseSemiringPotential<double, InsidePotential> {
public:
	InsidePotential(double value) : BaseSemiringPotential<double, InsidePotential>(normalize(value)) { }
	InsidePotential() : BaseSemiringPotential<double, InsidePotential>(zero()) { }

	inline InsidePotential& operator+=(const InsidePotential& rhs) {
		value = value + rhs.value;
		return *this;
	}
	inline InsidePotential& operator*=(const InsidePotential& rhs) {
		value = value * rhs.value;
		return *this;
	}

		friend inline InsidePotential operator/(InsidePotential lhs, const InsidePotential &rhs) {
			lhs.value /= rhs.value;
			return lhs;
	}

	static InsidePotential one() { return InsidePotential(1.0); }
	static InsidePotential zero() { return InsidePotential(0.0); }

	double& normalize(double& val) {
		if (val < 0.0) val = 0.0;
		if (val >= 1.0) val = 1.0;
		return val;
	}

// protected:
	BASE_SEMIRING_REGISTRY_DECLARATION(InsidePotential);
};

/**
 * Implements the Real type of semiring as described in Huang 2006
 * +: min
 * *: +
 * 0: INF
 * 1: 0
 */
class RealPotential : public BaseSemiringPotential<double, RealPotential> {
public:
	RealPotential(double value) : BaseSemiringPotential<double, RealPotential>(normalize(value)) { }
	RealPotential() : BaseSemiringPotential<double, RealPotential>(zero()) { }

	inline RealPotential& operator+=(const RealPotential& rhs) {
		value = std::min(value, rhs.value);
		return *this;
	}
	inline RealPotential& operator*=(const RealPotential& rhs) {
		value = value + rhs.value;
		return *this;
	}

	static RealPotential one() { return RealPotential(0.0); }
	static RealPotential zero() { return RealPotential(INF); }
	static double randValue() { return dRand(one(), zero()); }


// protected:
	BASE_SEMIRING_REGISTRY_DECLARATION(RealPotential);
};

/**
 * Implements the Inside type of semiring as described in Huang 2006
 * +: min
 * *: +
 * 0: INF
 * 1: 0
 */
class TropicalPotential : public BaseSemiringPotential<double, TropicalPotential> {
public:
	TropicalPotential(double value) : BaseSemiringPotential<double, TropicalPotential>(normalize(value)) { }
	TropicalPotential() : BaseSemiringPotential<double, TropicalPotential>(zero()) { }

	inline TropicalPotential& operator+=(const TropicalPotential& rhs) {
		value = value + rhs.value;
		return *this;
	}
	inline TropicalPotential& operator*=(const TropicalPotential& rhs) {
		value = value * rhs.value;
		return *this;
	}

	static TropicalPotential one() { return TropicalPotential(0.0); }
	static TropicalPotential zero() { return TropicalPotential(INF); }
	static double randValue() { return dRand(one(), zero()); }

	double& normalize(double& val) {
		if (val < 0.0) val = 0.0;
		return val;
	}

// protected:
	BASE_SEMIRING_REGISTRY_DECLARATION(TropicalPotential);
};


/**
 * Implements the Counting type of semiring as described in Huang 2006
 * +: +
 * *: *
 * 0: 0
 * 1: 1
 */
class CountingPotential : public BaseSemiringPotential<int, CountingPotential> {
public:
	CountingPotential(int value) : BaseSemiringPotential<int, CountingPotential>(normalize(value)) { }
	CountingPotential() : BaseSemiringPotential<int, CountingPotential>(zero()) { }

	inline CountingPotential& operator+=(const CountingPotential& rhs) {
		value = value + rhs.value;
		return *this;
	}
	inline CountingPotential& operator*=(const CountingPotential& rhs) {
		value = value * rhs.value;
		return *this;
	}

	static CountingPotential one() { return CountingPotential(1); }
	static CountingPotential zero() { return CountingPotential(0); }
	static int randValue() { return rand(); }

	int& normalize(int& val) {
		if(val < 0) val = 0;
		return val;
	}

// protected:
	BASE_SEMIRING_REGISTRY_DECLARATION(CountingPotential);
};

/**
 * Comparison pair. *Experimental*
 * Type (s, t) op (s', t')
 * +: if (s > s') then (s, t) else (s', t')
 * *: (s * s', t * t')
 * 0: (0, 0)
 * 1: (1, 1)
 */
template<typename SemiringComp, typename SemiringOther>
class CompPotential : public BaseSemiringPotential<std::pair<SemiringComp, SemiringOther>, CompPotential<SemiringComp, SemiringOther> > {
public:
	typedef std::pair<SemiringComp, SemiringOther> MyVal;
	typedef CompPotential<SemiringComp, SemiringOther> MyClass;
	using BaseSemiringPotential<MyVal, MyClass>::value;

	CompPotential(MyVal value) : BaseSemiringPotential<MyVal, MyClass>(normalize(value)) { }
	CompPotential() : BaseSemiringPotential<MyVal, MyClass>(zero()) { }

	inline MyClass& operator+=(const MyClass& rhs) {
		if (value.first < rhs.value.first) value = rhs.value;
		return *this;
	}

	inline MyClass& operator*=(const MyClass& rhs) {
		value.first = value.first * rhs.value.first;
		value.second = value.second * rhs.value.second;
		return *this;
	}

	static const MyClass one() { return MyClass(MyVal(SemiringComp::one(), SemiringOther::one())); }
	static const MyClass zero() { return MyClass(MyVal(SemiringComp::zero(), SemiringOther::zero())); }

	MyVal& normalize(MyVal& val) {
		val.first = normalize(val.first);
		val.second = normalize(val.second);
		return val;
	}

// protected:
// 	BASE_SEMIRING_REGISTRY_DECLARATION(CompPotential);
};


typedef pair<int, int> SparsePair;
typedef vector<SparsePair> SparseVector;

/**
 * Sparse vector. *Experimental*
 *
 * +: Elementwise min
 * *: Elementwise +
 * 0: Empty Vector
 * 1: Empty Vector
 */
class SparseVectorPotential : public BaseSemiringPotential<SparseVector, SparseVectorPotential> {
public:
	SparseVectorPotential(const SparseVector vec) : BaseSemiringPotential<SparseVector, SparseVectorPotential>(vec) { }
	SparseVectorPotential() : BaseSemiringPotential<SparseVector, SparseVectorPotential>(SparseVectorPotential::zero()) { }

	inline SparseVectorPotential& operator+=(const SparseVectorPotential& rhs) {
		return *this;
	}

	inline SparseVectorPotential& operator*=(const SparseVectorPotential& rhs);

	static SparseVectorPotential one() { return SparseVectorPotential(SparseVector()); }
	static SparseVectorPotential zero() { return SparseVectorPotential(SparseVector()); }
	static SparseVector randValue();

// protected:
	BASE_SEMIRING_REGISTRY_DECLARATION(SparseVectorPotential);
};

/**
 * Tree. *Experimental*
 *
 * +: No action
 * *: NULL if either is NULL. Otherwise create a new node with rhs.value and this->value as tails
 * 0: Empty Vector
 * 1: Empty Vector
 */
class TreePotential : public BaseSemiringPotential<Hypernode *, TreePotential> {
public:
TreePotential(Hypernode *value) : BaseSemiringPotential<Hypernode *, TreePotential>(normalize(value)) { }
TreePotential() : BaseSemiringPotential<Hypernode *, TreePotential>(zero()) { }

	inline TreePotential& operator+=(const TreePotential& rhs) {
		return *this;
	}

	inline TreePotential& operator*=(const TreePotential& rhs) {
		if (rhs.value == NULL or value == NULL) {
			value = NULL;
		} else {
			vector<HNode> tails;
			tails.push_back(value);
			tails.push_back(rhs.value);
			Hypernode *node = new Hypernode("");
			Hyperedge *edge = new Hyperedge("", node, tails);
			node->add_edge(edge);
			value = node;
		}
		return *this;
	}

	static TreePotential one() {
		return TreePotential(new Hypernode(""));
	}
	static const TreePotential zero() { return TreePotential(NULL); }

// protected:
	// BASE_SEMIRING_REGISTRY_DECLARATION(TreePotential);
};


// Classes used to associate projections with Hypergraphs

class HypergraphProjection;

template<typename SemiringType>
class HypergraphPotentials {
	typedef SemiringType S;
	typedef typename SemiringType::ValType V;
 public:
	HypergraphPotentials(const Hypergraph *hypergraph,
						const vector<V> &potentials,
						V bias)
	: hypergraph_(hypergraph),
		potentials_(potentials),
		bias_(bias) {
			assert(potentials.size() == hypergraph->edges().size());
	}

	HypergraphPotentials(const Hypergraph *hypergraph)
		: hypergraph_(hypergraph),
			potentials_(hypergraph->edges().size(), SemiringType::one()),
			bias_(SemiringType::one()) {}

	V dot(const Hyperpath &path) const {
		path.check(*hypergraph_);
		V score = SemiringType::one();
		foreach (HEdge edge, path.edges()) {
			score *= potentials_[edge->id()];
		}
		return score * bias_;
	}

	V score(HEdge edge) const { return potentials_[edge->id()]; }
	const inline V& operator[] (HEdge edge) const {
		return potentials_[edge->id()];
	}
	inline V& operator[] (HEdge edge) {
		return potentials_[edge->id()];
	}

	void insert(const HEdge& edge, const V& val) {
		potentials_[edge->id()] = val;
	}

	const V &bias() const { return bias_; }
	V &bias() { return bias_; }

	HypergraphPotentials<S> *project_potentials(
		const HypergraphProjection &projection) const;

	/**
	 * Pairwise "times" with another set of potentials.
	 *
	 * @return New hypergraphpotentials.
	 */
	HypergraphPotentials<S> *times(
			const HypergraphPotentials<V> &potentials) const;

	void check(const Hypergraph &graph) const {
		if (!graph.same(*hypergraph_)) {
			throw HypergraphException("Hypergraph does not match potentials.");
		}
	}

	void check(const HypergraphPotentials<S> &potentials) const {
		if (!potentials.hypergraph_->same(*hypergraph_)) {
			throw HypergraphException("Hypergraph potentials do not match potentials.");
		}
	}

	const Hypergraph *hypergraph() const { return hypergraph_; }

 protected:
	const Hypergraph *hypergraph_;
	vector<V> potentials_;
	V bias_;
};


class HypergraphProjection {
 public:
	HypergraphProjection(const Hypergraph *original,
											 const Hypergraph *_new_graph,
											 const vector<HNode> *node_map,
											 const vector<HEdge> *edge_map)
			: original_graph(original),
			new_graph(_new_graph),
			node_map_(node_map),
			edge_map_(edge_map) {
				assert(node_map->size() == original_graph->nodes().size());
				assert(edge_map->size() == original_graph->edges().size());
#ifndef NDEBUG
				foreach (HNode node, *node_map) {
					assert(node == NULL ||
								 node->id() < (int)_new_graph->nodes().size());
				}
				foreach (HEdge edge, *edge_map) {
					assert(edge == NULL ||
								 edge->id() < (int)_new_graph->edges().size());
				}
#endif
			}

	~HypergraphProjection() {
		delete node_map_;
		delete edge_map_;
	}

	static HypergraphProjection *project_hypergraph(
			const Hypergraph *hypergraph,
			const HypergraphPotentials<BoolPotential> &edge_mask);

	HEdge project(HEdge original) const {
		return (*edge_map_)[original->id()];
	}

	HNode project(HNode original) const {
		return (*node_map_)[original->id()];
	}

	const Hypergraph *original_graph;
	const Hypergraph *new_graph;

 private:

	// Owned.
	const vector<HNode> *node_map_;
	const vector<HEdge> *edge_map_;
};

#endif // HYPERGRAPH_SEMIRING_H_
