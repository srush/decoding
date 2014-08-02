from pydecode._pydecode import *

def _get_type(weight_type):
    if weight_type is None:
        return LogViterbi
    else:
        return weight_type

def inside(graph, weights, weight_type=None, chart=None):
    r"""
    Compute the inside table for the hypergraph and weights.

    Formally, given a hyperedge weight vector :math:`w` in
    :math:`\mathbb{S}^{{\cal E}}`, the function computes the inside
    vector :math:`C` in :math:`\mathbb{S}^{{\cal V}}` defined for all vertices
    :math:`v` as

    .. math::

      C_v = \bigoplus_{p \in I_v} w_{p_1} \otimes w_{p_2} \otimes \ldots \otimes w_{p_n}

    where :math:`I_v` is the set of paths inside of vertex :math:`v` and :math:`p_1 \ldots p_n` are
    the hyperedges in path :math:`p`.

    Parameters
    ----------

    graph : :py:class:`Hypergraph`
      The hypergraph :math:`({\cal V}, {\cal E})`.

    weights : ndarray
      The weight of each hyperedge. Represented as a vector in :math:`\mathbb{S}^{{\cal E}}`.

    weight_type : weight-type, optional
      A weight-type semiring; default: LogViterbi. See :ref:`weight_types` for full list. Type :math:`\mathbb{S}` must agree with weights.

    chart : ndarray, optional
      A chart buffer to reuse. Vector in :math:`\mathbb{S}^{{\cal V}}`.

    Returns
    -------

    chart : ndarray
       The computed inside chart :math:`C`. Represented as a vector in :math:`\mathbb{S}^{{\cal V}}`.
       Each element corresponds to the sum of the scores of each path
       "below" vertex v.
    """
    return _get_type(weight_type).inside(graph, weights, chart)


def outside(graph, weights, inside_chart, weight_type=None, chart=None):
    r"""
    Compute the outside table for the hypergraph and weights.

    Formally, given a hyperedge weight vector :math:`w` in
    :math:`\mathbb{S}^{{\cal E}}`, the function computes the outside
    vector :math:`C` in :math:`\mathbb{S}^{{\cal V}}` defined for all hyperedges
    :math:`v` as

    .. math::

      C_v = \bigoplus_{p \in O_v} w_{p_1} \otimes w_{p_2} \otimes \ldots \otimes w_{p_n}

    where :math:`O_v` is the set of partial paths outside of vertex :math:`v` and :math:`p_1 \ldots p_n` are
    the hyperedges in path :math:`p`.


    Parameters
    -----------

    graph : :py:class:`Hypergraph`
      The hypergraph :math:`({\cal V}, {\cal E})`.

    weights : ndarray
      The weight of each hyperedge. Represented as a vector in :math:`\mathbb{S}^{{\cal E}}`.


    inside_chart : ndarray
       The associated inside chart. Compute by calling
       :py:function:`inside`.  Must be the same type as weights.

    weight_type : weight-type, optional
      A weight-type semiring; default: LogViterbi. See :ref:`weight_types` for full list. Type :math:`\mathbb{S}` must agree with weights.

    chart : ndarray, optional
      A chart buffer to reuse. Vector in :math:`\mathbb{S}^{{\cal V}}`.

    Returns
    ---------

    chart : ndarray
       The computed ouside chart :math:`C`. Represented as a vector in :math:`\mathbb{S}^{{\cal V}}`.
       Each element corresponds to the sum of the scores of each path
       outside of vertex v.
    """
    return _get_type(weight_type).outside(graph, weights, inside_chart, chart)


def viterbi(graph, weights,
            weight_type=None, chart=None, back_pointers=None, mask=None):
    _get_type(weight_type).viterbi(graph, weights, chart,
                 back_pointers, mask, get_path=False)

def best_path(graph, weights,
              weight_type=None, chart=None, back_pointers=None, mask=None):
    r"""
    Find the best path through a hypergraph.

    Parameters
    ----------

    graph : :py:class:`Hypergraph`
      The hypergraph :math:`({\cal V}, {\cal E})`.

    weights : ndarray
      The weight of each hyperedge. Represented as a vector in :math:`\mathbb{S}^{{\cal E}}`.


    weight_type : weight-type, optional
      A weight-type semiring; default: LogViterbi. See :ref:`weight_types` for full list. Type :math:`\mathbb{S}` must agree with weights.

    chart : ndarray, optional
      A chart buffer to reuse. Vector in :math:`\mathbb{S}^{{\cal V}}`.

    back_pointer : ndarray, optional
      A back pointer buffer to reuse. Int-vector of size :math:`|{\cal V}|`.

    mask : ndarray, optional
      Pruning mask. Boolean-vector of size :math:`|{\cal V}|`. Only unmasked-vertices are considered.

    Returns
    -------
    path : :py:class:`Path`
      The highest-scoring hyperpath under the given weights.
    """

    return _get_type(weight_type).viterbi(graph, weights,
                        chart=chart,
                        back_pointers=back_pointers,
                        mask=mask)

def kbest(graph, weights,
          weight_type=None, chart=None, back_pointers=None, mask=None):
    r"""
    Find the k-best paths through a hypergraph.

    Parameters
    ----------

    graph : :py:class:`Hypergraph`
      The hypergraph :math:`({\cal V}, {\cal E})`.

    weights : ndarray
      The weight of each hyperedge. Represented as a vector in :math:`\mathbb{S}^{{\cal E}}`.

    weight_type : weight-type, optional
      A weight-type semiring; default: LogViterbi. See :ref:`weight_types` for full list. Type :math:`\mathbb{S}` must agree with weights.

    Returns
    -------
    paths : list of :py:class:`Path`
      The k-highest-scoring hyperpaths under the given weights.
    """
    raise NotImplementedError()

def marginals(graph, weights,
              inside_chart=None,
              outside_chart=None,
              weight_type=None):
    r"""
    Compute hyperedge marginals based on hypergraph and weights.

    Formally, given a hyperedge weight vector :math:`w` in
    :math:`\mathbb{S}^{{\cal E}}`, the function computes the hyperedge marginal
    vector :math:`M` in :math:`\mathbb{S}^{{\cal E}}` defined for all
    :math:`e` as

    .. math::

      M_e = \bigoplus_{p \in P: e \in p} w_{p_1} \otimes w_{p_2} \otimes \ldots \otimes w_{p_n}

    where :math:`P` is the set of all paths in the hypergraph, :math:`p_1 \ldots p_n` are
    the hyperedges in path :math:`p`, and the constraint :math:`e \in p` requires that hyperedge
    :math:`e` appears in the path.

    Parameters
    -----------

    graph : :py:class:`Hypergraph`
      The hypergraph :math:`({\cal V}, {\cal E})`.

    weights : ndarray
      The weight of each hyperedge. Represented as a vector in :math:`\mathbb{S}^{{\cal E}}`.


    inside_chart : ndarray, optional
       The associated inside chart. Compute by calling
       ``inside``.  Must be the same type as weights.
       If not provide will be calculated as part of the function.

    outside_chart : ndarray, optional
       The associated outside chart. Compute by calling
       ``outside``.  Must be the same type as weights.
       If not provide will be calculated as part of the function.

    weight_type : weight-type, optional
      A weight-type semiring; default: LogViterbi. See :ref:`weight_types` for full list. Type :math:`\mathbb{S}` must agree with weights.

    Returns
    ---------

    marginals : ndarray
       The computed marginal vector :math:`M`. Represented as a vector in :math:`\mathbb{S}^{{\cal E}}`.
       Each element corresponds to the sum of the scores of each path passing through each hyperedge :math:`e`.
    """
    my_inside = inside_chart
    if my_inside is None:
        my_inside = inside(graph, weights, weight_type=weight_type)

    my_outside = outside_chart
    if my_outside is None:
        my_outside = \
            outside(graph, weights, inside_chart=my_inside, weight_type=weight_type)


    return _get_type(weight_type).compute_marginals(graph, weights,
                                  my_inside, my_outside)


def draw(graph, edge_labels=None, vertex_labels=None,
         paths=None, formatter=None, labels=False, out=None):
    r"""
    Draw the hypergraph using GraphViz.

    When run in IPython notebook, will draw the graph directly. Otherwise
    an output file should be specified with ``out``.

    .. note::

       Requires graphviz, networkx, and pydot.

    Parameters
    -----------

    graph : :py:class:`Hypergraph`
      The hypergraph :math:`({\cal V}, {\cal E})`.

    edge_labels : ndarray, optional
       A :math:`|{\cal E}|`-vector re-labeling the hyperedges .

    vertex_labels : ndarray, optional
       A :math:`|{\cal V}|`-vector re-labeling the vertices.

    paths : list of :py:class:`Path`, optional
       A list of paths to be highlighted in the visualization.

    formatter : :py:class:`HypergraphFormatter`, optional
       A custom formatter inheriting from ``HypergraphFormatter``
       for displaying the hypergraph.

    out : filepath, optional
       A filepath to write out the hypergraph image.
    """
    import pydecode.display
    my_formatter = formatter
    if formatter is None:
        my_formatter = pydecode.display.HypergraphFormatter()
    if labels:
        my_formatter.set_weights(graph.labeling)
        my_formatter.set_node_weights(graph.node_labeling)
    else:
        my_formatter.set_weights(edge_labels)
        my_formatter.set_node_weights(vertex_labels)
    if paths is not None:
        my_formatter.set_paths(paths)
    drawer = pydecode.display.HypergraphDraw(graph, my_formatter)

    if out is None:
        return drawer.to_ipython()
    else:
        drawer.to_image(out)


def transform(graph, label_array, weight_type=None):
    r"""
    Transform a label-sized array into an edge-sized array.
    Labels are often a smaller, and more natural way for specifying
    weights. This function efficiently transforms a label array into
    a weight array for use with the hypergraph functions (such as
    ``best_path``, ``marginals``, etc.)

    Parameters
    -----------
    graph : :py:class:`Hypergraph`
      A labeled hypergraph :math:`({\cal V}, {\cal E})` with
      labeling in :math:`L`.

    label_array : ndarray
      An array of size :math:`|L|`. Type depends of ``weight_type``.

    weight_type : weight-type, optional
      A weight-type semiring; default: LogViterbi. Used
      to give weight :math:`\bar{1}` to unlabeled (-1) edges.
      Type :math:`\mathbb{S}` must agree with label_array.

    Returns
    -------
    weights : ndarray
      The corresponding weight array. Represented as a vector in :math:`\mathbb{S}^{{\cal E}}`.
    """
    return label_array.take(graph.labeling, mode='clip')

def inverse_transform(graph, weights, weight_type=None):
    r"""

    Transform a edge-sized array into an array over labels.  Labels
    can give a better representation of the underlying output.  For
    instance, the function can be used to transform the output of
    `marginals` to give values over labels instead of edges.

    Parameters
    -----------
    graph : :py:class:`Hypergraph`
      A labeled hypergraph :math:`({\cal V}, {\cal E})` with
      labeling in :math:`L`.

    weights : ndarray
      A weight of each hyperedge. Represented as a
      vector in :math:`\mathbb{S}^{{\cal E}}`.


    weight_type : weight-type, optional
      A weight-type semiring; default: LogViterbi. Used
      to give a :math:`\oplus` operation to combine weights
      for labels that are used at multiple edges.
      Type :math:`\mathbb{S}` must agree with label_array.

    Returns
    -------
    label : ndarray
      The corresponding label array. Represented as a vector in :math:`\mathbb{S}^{L}`.
    """
    raise NotImplementedError()
    # Slow implementation, make faster.
    return _get_type(weight_type).transform_to_labels(weights)

def binary(graph):
    """
    Create an equivalent hypergraph with binary hyperedges.

    Constructs a new hypergraph with binary-branching hyperedges. Each
    k-ary edge is converted to (k-1) right-branching binary
    edges. Labels are placed at the new edge closest to the root.

    Parameters
    -----------
    graph : :py:class:`Hypergraph`
      A hypergraph :math:`({\cal V}, {\cal E})`.

    Returns
    --------
    binarized_graph : :py:class:`Hypergraph`
       The binarized hypergraph. The hypergraph will maintain
       the hyperedge labeling, but not edge id's.
    """
    return binarize_internal(graph)

def filter(graph, mask):
    """
    Filter a hypergraph based on an edge mask.

    Edges with value 0 are explicitly pruned.
    Additionaly edges (and vertices) will be pruned
    if they are no longer on a valid path.

    Parameters
    -----------
    graph : :py:class:`Hypergraph`
      A hypergraph :math:`({\cal V}, {\cal E})`.

    mask : bool ndarray
        A pruning mask represented as a :math:`\{0,1\}^{\cal E}` vector.

    Returns
    --------
    filtered_graph : :py:class:`Hypergraph`
       The filtered hypergraph. The hypergraph will maintain both
       the hyperedge and vertex labeling, but not edge id's.
    """
    return filter_internal(graph, mask)


def lp(graph, weights):
    """
    Construct a linear program for the best-path.

    .. note::

       Requires PuLP_.

    .. _PuLP: http://pythonhosted.org/PuLP/

    Parameters
    -----------
    graph : :py:class:`Hypergraph`
      A hypergraph :math:`({\cal V}, {\cal E})`.

    weights : ndarray
      The weight of each hyperedge. Must be LogViterbi weights.
      Represented as a vector in :math:`\mathbb{R}^{{\cal E}}`.

    Returns
    --------
    lp : :py:class:`HypergraphLP`
      The hypergraph best-path problem expressed as a linear program.
    """
    import pydecode.lp
    return pydecode.lp.HypergraphLP.make_lp(graph, weights)

# Higher-level interface.

def _check_output_weights(dp, out_weights):
    if dp.outputs.size != out_weights.size:
        raise ValueError("Weights do not match output shape: %s != %s"
                         %(out_weights.shape, dp.outputs.shape))

def path_output(dp, path):
    """
    Convert a hypergraph path to the corresponding
    dynamic programming outputs.

    Parameters
    -----------
    dp : DynamicProgram

    path : Path

    Returns
    --------
    outputs : outputs x output_width matrix
       Matrix of outputs. Output_width is the width of an output
       and outputs is the number of non-zero outputs in the path.
    """
    int_output = dp.output_indices.take(path.edge_indices,
                                        mode="clip")
    return np.array(np.unravel_index(int_output[int_output!=-1],
                                     dp.outputs.shape)).T

def vertex_items(dp):
    """
    Reconstructs the items associated with each
    hypergraph vertex.

    Relatively slow, mainly for debugging.

    Parameters
    -----------
    dp : DynamicProgram

    Returns
    -------
    items : |V| x item_width matrix
       Matrix of items. Item_width is the width of an item
       and |V| is the number of vertices.
    """
    return np.array(np.unravel_index(dp.item_indices,
                                     dp.items.shape)).T


def hyperedge_outputs(dp):
    """
    Reconstructs the outpus associated with each
    hypergraph hyperedge.

    Relatively slow, mainly for debugging.

    Returns
    -------
    items : |E| x output_width matrix
       Matrix of items. Output width is the width of an output
       and |E| is the number of hyperedges.
    """
    return np.unravel_index(dp.output_indices,
                            dp.outputs.shape)


def _map_weights(dp, out_weights):
    return out_weights.take(dp.output_indices, mode='clip')

def map_items(dp, out_items):
    return out_items.take(dp.item_indices, mode='clip')

def _map_weights2(dp, out_weights):
    return dp.output_matrix.T * out_weights.ravel()

def argmax(dp, out_weights,
           weight_type=None, chart=None, mask=None):
    """
    Find the highest scoring output structure in a
    dynamic program.

    Returns
    -------
    outputs : output x output_width matrix
       Matrix of outputs.
    """
    _check_output_weights(dp, out_weights)
    weights = _map_weights(dp, out_weights)
    if mask != None:
        new_mask = map_items(dp, mask)
        path = best_path(dp.hypergraph, weights,
                         weight_type, chart=chart, mask=new_mask)
    else:
        path = best_path(dp.hypergraph, weights,
                         weight_type, chart=chart)
    return path_output(dp, path)


def fill(dp, out_weights, weight_type=None, chart=None):
    """
    Fill in a dynamic programming chart based on a set of weights.

    Parameters
    ----------
    dp : DynamicProgram

    out_weights : array
       An array in the shape of dp.outputs

    Returns
    -------
    chart : array
       An array in the shape of items.
    """
    _check_output_weights(dp, out_weights)
    weights = _map_weights(dp, out_weights)
    new_chart = inside(dp.hypergraph, weights,
                       weight_type, chart)
    return new_chart.reshape(dp.items.shape)


def output_marginals(dp,
                     out_weights,
                     weight_type=None):
    """
    Compute marginals for the outputs of a dynamic program.

    Parameters
    ----------
    dp : DynamicProgram

    out_weights : array

    Returns
    -------
    output_marginals : array
       An array in the shape of dp.outputs with marginal values.
    """
    _check_output_weights(dp, out_weights)
    weights = _map_weights(dp, out_weights)
    _, edge_marginals = marginals(dp.hypergraph,
                                  weights, None, None, weight_type)
    return (dp.output_matrix * edge_marginals).reshape(
        dp.outputs.shape)

def item_marginals(dp,
                   out_weights,
                   weight_type=None):
    """
    Compute marginals for the outputs of a dynamic program.

    Parameters
    ----------
    dp : DynamicProgram

    out_weights : array

    Returns
    -------
    item_marginals : array
       An array in the shape of dp.items with marginal values.
    """
    _check_output_weights(dp, out_weights)
    weights = _map_weights(dp, out_weights)
    node_marginals, _ = marginals(dp.hypergraph,
                                  weights, None, None, weight_type)
    return (dp.item_matrix * node_marginals).reshape(
        dp.items.shape)

def score_outputs(dp, outputs, out_weights,
                  weight_type=None):
    """

    """
    indices = np.ravel_multi_index(outputs.T,
                                   dp.outputs.shape)
    return np.prod(map(weight_type.Value,
                       out_weights.ravel()[indices]))
