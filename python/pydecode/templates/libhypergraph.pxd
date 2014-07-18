cimport numpy as np
from libcpp.string cimport string
from libcpp.vector cimport vector
from libcpp.map cimport map
from libcpp.set cimport set
from libcpp cimport bool

cdef extern from "Hypergraph/Hypergraph.hh":
    # cdef cppclass CHypernode "Hypernode":
    #     int id()
    #     vector[int ] edges()
    cdef cppclass CHypergraph "Hypergraph":
        CHypergraph(bool)
        void set_expected_size(int, int, int)
        int root()
        vector[int] edges(int)
        bool terminal(int)
        int tail_nodes(int)
        int tail_node(int, int)
        int head(int)
        int start_node()
        int add_terminal_node()
        bool end_node()
        int id()
        int new_id(int)
        int add_edge(vector[int]) except +
        void finish(bool reconstruct) except +
        vector[int] nodes()
        vector[int] edges()
        vector[int] heads()

    cdef cppclass CHyperpath "Hyperpath":
        CHyperpath(const CHypergraph *graph,
                   const vector[int] nodes,
                   const vector[int] edges) except +
        vector[int] edges()
        vector[int] nodes()
        int has_edge(int)
        bool equal(const CHyperpath path)

cdef class Labeling:
    cdef edge_labels
    cdef node_labels

cdef class _LazyEdges:
    cdef Hypergraph _graph
    cdef vector[int] _edges
    cdef init(self, vector[int])

cdef class _LazyVertices:
    cdef Hypergraph _graph
    cdef vector[int] _nodes
    cdef init(self, vector[int])

cdef class Hypergraph:
    cdef CHypergraph *thisptr
    cdef Labeling labeling
    cdef _cached_edges
    cdef bool unary
    cdef Hypergraph init(self, const CHypergraph *ptr, Labeling labeling)

cdef class Vertex:
    cdef int nodeptr
    cdef CHypergraph *graphptr
    cdef Hypergraph graph

    cdef Vertex init(self, int nodeptr,
                   Hypergraph graph)

cdef class Edge:
    cdef int edgeptr
    cdef Hypergraph graph

    cdef Edge init(self, int edge, Hypergraph graph, bool unfinished=?)
    cdef bool unfinished

cdef class Path:
    cdef const CHyperpath *thisptr
    cdef Hypergraph graph
    cdef vector
    cdef _vertex_vector
    cdef np.ndarray _edge_indices
    cdef np.ndarray _vertex_indices

    cdef Path init(self, const CHyperpath *path, Hypergraph graph)
    cdef public equal(Path self, Path other)

cdef extern from "Hypergraph/Map.hh":
    cdef cppclass CHypergraphMap "HypergraphMap":
        int map_node(int)
        int map_edge(int)
        const CHypergraph *domain_graph()
        const CHypergraph *range_graph()
        const vector[int] edge_map()
