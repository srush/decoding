// Copyright [2013] Alexander Rush

#ifndef HYPERGRAPH_HYPERGRAPH_H_
#define HYPERGRAPH_HYPERGRAPH_H_

#include <cassert>
#include <exception>
#include <set>
#include <string>
#include <vector>

#include "./common.h"

using namespace std;

class Hypernode;
class Hyperedge;
typedef const Hypernode *HNode;
typedef vector <const Hypernode *> HNodes;
typedef int HEdge;
/* typedef vector<const Hyperedge *> HEdges; */

struct HypergraphException : public exception {
  string s;
  explicit HypergraphException(string ss) : s(ss) {}
  ~HypergraphException() throw() {}
  const char* what() const throw() { return s.c_str(); }
};

class HypergraphAccessException : public HypergraphException {};
class HypergraphMatchException : public HypergraphException {};
class HypergraphConstructionException : public HypergraphException {};

/* class Hyperedge { */
/*  public: */
/*   Hyperedge(HNode head, */
/*             const vector<HNode> &tails) */
/*     : id_(-1), */
/*       head_(head), */
/*       tail_nodes_(tails) {} */

/*   /\** */
/*    * Get the id of the edge. */
/*    *\/ */
/*   int id() const { return id_; } */

/*   void set_id(int id) { id_ = id; } */

/*   /\** */
/*    * Get the head node of the edge. */
/*    *\/ */
/*   HNode head_node() const { return head_; } */

/*   /\** */
/*    * Get the tail nodes of the hyperedge in order. */
/*    *\/ */
/*   const vector<HNode> &tail_nodes() const { return tail_nodes_; } */

/*   /\** */
/*    * Topological order on edges. */
/*    *\/ */
/*   bool operator<(const Hyperedge *edge2) const { */
/*     return id() < edge2->id(); */
/*   } */

/*  private: */
/*   int id_; */
/*   HNode head_; */
/*   vector<HNode> tail_nodes_; */
/* }; */


/**
 * Hypernode - Constant representation of a hypernode in a hypergraph.
 * Accessors for edges above and below.
 */
class Hypernode {
  public:
  explicit Hypernode()
    : id_(-1) {}

  int id() const { return id_; }

  void set_id(int id) { id_ = id; }

  void add_edge(HEdge edge) {
    edges_.push_back(edge);
  }

  /**
   * Get all hyperedges with this hypernode as head.
   */
  const vector<HEdge> &edges() const { return edges_; }

  /**
   * Is the node a terminal node.
   */
  bool terminal() const { return edges_.size() == 0; }

 private:
  int id_;
  vector<HEdge> edges_;
};

class Hypergraph {
 public:
  Hypergraph()
      : terminal_lock_(true), lock_(false),
      temp_nodes_(0), temp_edges_(0),
      id_(ID++) {}

    ~Hypergraph() {
        /* foreach (HEdge edge, edges_) { */
        /*     delete edge; */
        /* } */
        foreach (HNode node, nodes_) {
            delete node;
        }
    }


  /**
   * Get the root of the hypergraph
   *
   * @return Hypernode at root
   */
  HNode root() const { return root_; }

  int id(HEdge edge) const { return edge; }
  int new_id(HEdge edge) const { return temp_edges_[edge]; }


  /**
   * Get all hypernodes in the hypergraph. Ordered topologically.
   * WARNING: Treat this as a const iterator.
   * @return Const iterator to hypernodes in hypergraph.
   */
  const vector<HNode> &nodes() const {
    return nodes_;
  }

  /**
   * Get all hyperedges in the hypergraph. Ordered topologically.
   * WARNING: Treat this as a const iterator.
   * @return Const iterator to edges in hypergraph .
   */
  const vector<HEdge> &edges() const { return edges_; }

  /* int edges() const { return edges_.size(); } */
  HNode head(HEdge edge) const { return edge_heads_[edge]; }
  int tail_nodes(HEdge edge) const { return edge_tails_[edge].size(); }
  HNode tail_node(HEdge edge, int tail) const { return edge_tails_[edge][tail]; }

  // Construction Code.

  /**
   * Create a new node and begin adding edges.
   */
  HNode add_terminal_node();

  HNode start_node();

  /* HEdge add_edge(const vector<HNode> &nodes); */
  HEdge add_edge(const vector<HNode> &nodes);

  /**
   * Returns true if the node was created.
   * Returns false if the node was removed (no children).
   */
  bool end_node();

  /**
   * Complete the hypergraph.
   */
  void finish() {
    if (temp_nodes_.size() == 0) {
      throw HypergraphException("Hypergraph has size 0.");
    }
    root_ = temp_nodes_[temp_nodes_.size() - 1];
    /* if (!(root == NULL || root_ == root)) { */
    /*   throw HypergraphException("Root is not expected root."); */
    /* } */

    fill();
    if (nodes_.size() == 0) {
      throw HypergraphException("Final hypergraph has node size 0.");
    }
    if (edges_.size() == 0) {
      throw HypergraphException("Final hypergraph has edge size 0.");
    }
    // TODO(srush) Run checks to make sure we are complete.
  }

  /**
   * Remove paths that do not reach the root.
   */
  void fill();

  /**
   * Is this hypergraph the same as other.
   */
  bool same(const Hypergraph &other) const { return other.id_ == id_; }

  int id() const { return id_; }

 private:
  // For construction.
  bool terminal_lock_;

  // The hypergraph is adding an edge. It is locked.
  bool lock_;

  // The current node being created.
  Hypernode *creating_node_;

  // List of temporary nodes (for construction).
  vector<Hypernode *> temp_nodes_;

  // List of temporary edges.
  vector<HEdge> temp_edges_;
  vector<vector<HNode> > temp_edge_tails_;
  vector<Hypernode *> temp_edge_heads_;

  // The true interface.

  // List of nodes guarenteed to be in topological order.
  vector<HNode> nodes_;


  // List of edges guarenteed to be in topological order.
  vector<HEdge> edges_;
  vector<vector<HNode> > edge_tails_;
  vector<HNode> edge_heads_;

  HNode root_;

  int id_;

  static int ID;
};

class Hyperpath {
 public:
  Hyperpath(const Hypergraph *graph,
            const vector<HEdge> &edges)
      : graph_(graph), edges_(edges) {
    HEdge last_edge = -1;
    foreach (HEdge edge, edges) {
        edges_set_.insert(graph->id(edge));
        if (last_edge != -1 && graph->id(last_edge) >= graph->id(edge)) {
            throw HypergraphException("Hyperpath is not in order.");
        }
        for (int i = 0; i < graph_->tail_nodes(edge); ++i) {
            HNode node = graph_->tail_node(edge, i);
            nodes_.push_back(node);
            nodes_set_.insert(node->id());
        }
        last_edge = edge;
    }
    nodes_.push_back(graph->root());
    nodes_set_.insert(graph->root()->id());
    }

  /**
   * Get the edges in the path. In topological order.
   */
  const vector<HEdge> &edges() const {
    return edges_;
  }

  const vector<HNode> &nodes() const {
    return nodes_;
  }

  /**
   * Is edge in the hyperpath.
   */
  bool has_edge(HEdge edge) const {
    return edges_set_.find(graph_->id(edge)) != edges_set_.end();
  }

  bool has_node(HNode node) const {
    return nodes_set_.find(node->id()) != nodes_set_.end();
  }


  /**
   * Is this hyperpath associated with the hypergraph.
   */
  void check(const Hypergraph &graph) const {
    if (!graph.same(*graph_)) {
      throw HypergraphException("Hypergraph does not match path.");
    }
  }

  bool equal(const Hyperpath &path) const {
      check(*path.graph_);
      if (edges_.size() != path.edges_.size()) return false;
      for (uint i = 0; i < edges_.size(); ++i) {
          if (graph_->id(edges_[i]) != graph_->id(path.edges_[i])) {
              return false;
          }
      }
      return true;
  }

 private:
  const Hypergraph *graph_;
  set<int> edges_set_;
  const vector<HEdge> edges_;
  set<int> nodes_set_;
  vector<HNode> nodes_;
};


#endif  // HYPERGRAPH_HYPERGRAPH_H_
