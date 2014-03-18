
## Simple Hypergraph Example

# In[1]:

import pydecode.hyper as ph
import pydecode.display as display


# In[4]:

hyp = ph.Hypergraph()
with hyp.builder() as b:
     n1 = b.add_node(label = "a")
     n2 = b.add_node(label = "b")
     n3 = b.add_node(label = "c")
     n4 = b.add_node(label = "d")
     n5 = b.add_node((([n1, n2], "edge1"),), label = "e")
     b.add_node([([n5], "edge3"), ([n3, n4], "edge2")], label = "root")

def build_potentials(label):
     return {"edge1" : 3, "edge2" : 1, "edge3" : 1}[label]
potentials = ph.Potentials(hyp).from_vector([build_potentials(edge.label) for edge in hyp.edges])


# Draw the graph

# In[5]:

display.HypergraphPotentialFormatter(hyp, potentials).to_ipython()


# Out[5]:

#     <IPython.core.display.Image at 0x2b58d10>

# In[6]:

path = ph.best_path(hyp, potentials)
display.HypergraphPathFormatter(hyp, [path]).to_ipython()


# Out[6]:

#     <IPython.core.display.Image at 0x2b403d0>
