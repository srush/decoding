from cython.operator cimport dereference as deref
from libcpp.string cimport string
from libcpp.vector cimport vector


cdef extern from "Hypergraph/Algorithms.h":
    Hyperpath *viterbi_path(const Hypergraph *graph,
                            const HypergraphWeights theta,
                            vector[double] *chart)

cdef extern from "Hypergraph/Hypergraph.h":
    cdef cppclass Hyperedge:
        string label()
        int id()
        const Hypernode *head_node()
        vector[const Hypernode *] tail_nodes()

    cdef cppclass Hypernode:
        vector[const Hyperedge *] edges()
        int id()

    cdef cppclass Hypergraph:
        Hypergraph()
        const Hypernode *root()
        const Hypernode *start_node()
        vector[const Hypernode *] nodes()
        vector[const Hyperedge *] edges()
        void end_node()
        const Hyperedge *add_edge(vector[const Hypernode *],
                                  string label)
        void finish()

    cdef cppclass Hyperpath:
        vector[const Hyperedge *] edges()


    cdef cppclass HypergraphWeights:
        HypergraphWeights(const Hypergraph *hypergraph,
                          const vector[double] weights,
                          double bias)
        double dot(const Hyperpath &path)

cdef extern from "Hypergraph/Constraints.h":
    cdef cppclass Constraint:
        Constrint(string label, int id)
        void set_constant(int _bias)
        void add_edge_term(const Hyperedge *edge, int coefficient)
        string label

    cdef cppclass HypergraphConstraints:
        HypergraphConstraints(const Hypergraph *hypergraph)
        Constraint *add_constraint(string label)
        int check_constraints(const Hyperpath path,
                              vector[const Constraint *] *failed,
                              vector[int] *count)


def viterbi(HGraph graph, Weights weights):
    cdef vector[double] chart
    cdef const Hyperpath *hpath = viterbi_path(graph.thisptr, deref(weights.thisptr), &chart)
    cdef Path path = Path()
    path.init(hpath)
    return path


cdef class HGraph:
    cdef Hypergraph *thisptr
    def __cinit__(self):
        self.thisptr = new Hypergraph()

    def builder(self):
        gb = GraphBuilder()
        gb.init(self.thisptr)
        return gb

    def edges_size(self):
        return self.thisptr.edges().size()

    def nodes_size(self):
        return self.thisptr.nodes().size()

    def edges(self):
        return convert_edges(self.thisptr.edges())

    def nodes(self):
        return convert_nodes(self.thisptr.nodes())

cdef class GraphBuilder:
    cdef Hypergraph *thisptr

    cdef init(self, Hypergraph *ptr):
        self.thisptr = ptr

    def __enter__(self):
        return self

    def __exit__(self, a, b, c):
        self.thisptr.finish()

    def add_terminal_node(self):
        node = Node()
        cdef const Hypernode *nodeptr = self.thisptr.start_node()
        self.thisptr.end_node()
        node.init(nodeptr)
        return node

    def add_node(self):
        node = Node()
        cdef const Hypernode *nodeptr = self.thisptr.start_node()
        node.init_mutable(self.thisptr, nodeptr)
        return node

cdef class Node:
    cdef const Hypernode *nodeptr
    cdef Hypergraph *graphptr
    cdef int edge_count

    def __cinit__(self):
        self.edge_count = 0

    cdef init_mutable(self, Hypergraph *graphptr, const Hypernode *nodeptr):
        self.graphptr = graphptr
        self.nodeptr = nodeptr

    cdef init(self, const Hypernode *nodeptr):
        self.nodeptr = nodeptr

    def id(self):
        return self.nodeptr.id()

    def edges(self):
        return convert_edges(self.nodeptr.edges())

    def __cinit__(self):
        pass

    def __enter__(self):
        return self

    def add_edge(self, tail_nodes, label):
        cdef vector[const Hypernode *] tail_node_ptrs
        for tail_node in tail_nodes:
            tail_node_ptrs.push_back((<Node> tail_node).nodeptr)
        edgeptr = self.graphptr.add_edge(tail_node_ptrs, label)
        self.edge_count += 1
        edge = Edge()
        edge.init(edgeptr)
        return edge

    def __exit__(self, a, b, c):
        print "exit"
        if self.edge_count == 0:
            assert False
        self.graphptr.end_node()


cdef class Edge:
    cdef const Hyperedge *edgeptr

    def __cinit__(self):
        pass

    cdef init(self, const Hyperedge *ptr):
        self.edgeptr = ptr

    def tail(self):
        return convert_nodes(self.edgeptr.tail_nodes())

    def head(self):
        return convert_node(self.edgeptr.head_node())

    def label(self):
        return self.edgeptr.label()

    def id(self):
        return self.edgeptr.id()


cdef convert_edges(vector[const Hyperedge *] edges):
    py_edges = []
    for edge in edges:
        py_edge = Edge()
        py_edge.init(edge)
        py_edges.append(py_edge)
    return py_edges

cdef convert_nodes(vector[const Hypernode *] nodes):
    py_nodes = []
    for node in nodes:
        py_nodes.append(convert_node(node))
    return py_nodes

cdef convert_node(const Hypernode * node):
    py_node = Node()
    py_node.init(node)
    return py_node

cdef class Path:
    cdef const Hyperpath *thisptr
    cdef init(self, const Hyperpath *path):
        self.thisptr = path

    def edges(self):
        return convert_edges(self.thisptr.edges())


cdef class Weights:
    cdef const HypergraphWeights *thisptr
    def __cinit__(self, HGraph hypergraph, vector[double] weights, double bias):
        self.thisptr = new HypergraphWeights(hypergraph.thisptr, weights, bias)

    def dot(self, Path path):
        cdef double result = self.thisptr.dot(deref(path.thisptr))
        return result

cdef class WeightBuilder:
    cdef vals
    cdef hypergraph
    def __cinit__(self, hypergraph):
        self.vals = {}
        self.hypergraph = hypergraph

    def set_weight(self, Edge edge, val):
        self.vals[edge.edgeptr.id()] = val

    def weights(self):
        cdef vector[double] weights
        weights.resize(self.hypergraph.edges_size(), 0)
        for i, w in self.vals.iteritems():
            weights[i] = w
        return Weights(self.hypergraph, weights, 0.0)

cdef class HConstraint:
    cdef Constraint *thisptr
    cdef init(self, Constraint *ptr):
        self.thisptr = ptr

    def set_constant(self, int constant):
        self.thisptr.set_constant(constant)

    def add_edge_term(self, Edge edge, int coefficient):
        self.thisptr.add_edge_term(edge.edgeptr, coefficient)

cdef class HConstraints:
    cdef HypergraphConstraints *thisptr
    def __cinit__(self, HGraph hypergraph):
        self.thisptr = new HypergraphConstraints(hypergraph.thisptr)

    def add(self, string label):
        cdef Constraint *cons
        cons = self.thisptr.add_constraint(label)
        cdef HConstraint hcons = HConstraint()
        hcons.init(cons)
        return hcons

    def check(self, Path path):
        cdef vector[const Constraint *] failed
        cdef vector[int] count
        self.thisptr.check_constraints(deref(path.thisptr),
                                       &failed,
                                       &count)
        ret = []
        for cons in failed:
            ret.append(cons.label)
        return ret

# cdef class Hyperedge:
#     cdef HyperedgeImpl *thisptr

#     def __cinit__(self, label,
#                   features,
#                   int id,
#                   tails,
#                   Hypernode head):
#         self.init(label, features, id, tails, head)

#     cdef init(self, string label, string features,
#               int id, tails, Hypernode head):
#         ptrs = [tail.thisptr for tail in tails]
#         cdef vector[HypernodeImpl *] tail_ptrs
#         for tail in tails:
#             tail_ptrs.push_back((<Hypernode>tail).thisptr)
#         self.thisptr = new HyperedgeImpl(label, features, id,
#                                          tail_ptrs, head.thisptr)

# cdef class Hypernode:
#     cdef HypernodeImpl *thisptr
#     def __cinit__(self, label, id):
#         self.thisptr = new HypernodeImpl(label, id)

#     def __dealloc__(self):
#         del self.thisptr
