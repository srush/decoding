---------------
Setup
---------------

Installation
=====================


The easiest way to install PyDecode is through pip.  ::

    $ pip install pydecode


The base functionality of the library requires numpy_, scipy_ and Boost_. To install Boost on Debian/Ubuntu run::

    $ sudo apt-get install libboost-dev


Optional Dependencies
====================

PyDecode also includes extensions that integrate with other Python libraries to provide additional functionality.

* **NetworkX, PyGraphviz, IPython**  (:ref:`display`)

  Provides methods for model visualization.

* **PyStruct**  (:ref:`structured`)

  Provides methods for training the parameters of a model .

* **PuLP and an LP solver** (:ref:`lp`)

  Provides methods for solving models using general-purpose
  linear-programming solvers.



Running Notebooks
=================

In addition to this documentation, the distribution also include a set
of example tutorials written as IPython_ notebooks.

These notebooks can be run locally after installation. Assuming ENV is
the base install directory (for instance using virtualenv_), the
notebooks can be run using::

    $ ipython notebook ENV/pydecode/notebooks/


.. _numpy: http://numpy.org
.. _scipy: http://scipy.org
.. _Boost: http://boost.org
.. _IPython: http://ipython.org
.. _virtualenv: http://virtualenv.readthedocs.org/en/latest/
