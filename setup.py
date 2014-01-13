from distutils.core import setup
from distutils.extension import Extension
import os.path

try:
    from Cython.Distutils import build_ext
    from Cython.Compiler.Version import version
    if int(version.split(".")[1]) < 19:
        raise ImportError("Bad version.")

except ImportError:
    use_cython = False
else:
    use_cython = True


ext_modules = [ ]
cmdclass = {}

if use_cython:
    ext_modules = [
        Extension("pydecode.hypergraph",
                  ["python/pydecode/hypergraph.pyx",
                   "src/Hypergraph/Hypergraph.cpp",
                   ],
                  language='c++',
                  #extra_compile_args=["-O0"],#"-ggdb"], #'-O2',
                  include_dirs=[r'src/', "."],
                  ),
        Extension("pydecode.potentials",
                  ["python/pydecode/potentials.pyx",
                   "src/Hypergraph/Semirings.cpp",
                   "src/Hypergraph/Algorithms.cpp",
                   "src/Hypergraph/Potentials.cpp",
                   ],
                  extra_objects=[os.path.abspath('python/pydecode/hypergraph.so')],
                  language='c++',
                  #extra_compile_args=["-O0"],#"-ggdb"], #'-O2',
                  include_dirs=[r'src/', "."],
                  ),

        Extension("pydecode.beam",
                  ["python/pydecode/beam.pyx",
                   "src/Hypergraph/BeamSearch.cpp",
                   ],
                  extra_objects=[os.path.abspath('python/pydecode/potentials.so'),
                                 os.path.abspath('python/pydecode/hypergraph.so')
                                 ],
                  language='c++',
                  #extra_compile_args=["-O0"],#"-ggdb"], #'-O2',
                  include_dirs=[r'src/', "."],
                  )
        ]
                             #extra_objects=['build/debug/src/libdecoding.a'],
                             #libraries=['decoding'])

    cmdclass = {'build_ext': build_ext}

else:
    ext_modules = [Extension("pydecode.hypergraph",
                             ["python/pydecode/hypergraph.cpp",
                              "src/Hypergraph/Hypergraph.cpp",
                              ],
                             language='c++',
                             include_dirs=[r'src/', "."],
                   ),
                   Extension("pydecode.potentials",
                             ["python/pydecode/potentials.cpp",
                              "src/Hypergraph/Semirings.cpp",
                              "src/Hypergraph/Algorithms.cpp",
                              "src/Hypergraph/Potentials.cpp",
                              ],
                             language='c++',
                             include_dirs=[r'src/', "."],
                             extra_objects=[os.path.abspath('python/pydecode/hypergraph.so')]
                   ),
                   ]

setup(
  name = 'pydecode',
  cmdclass = cmdclass,
  packages=['pydecode'],
  package_dir={'pydecode': 'python/pydecode'},
  ext_modules = ext_modules,
  requires=["networkx", "pandas"],
  version = '0.1.24',
  description = 'A dynamic programming toolkit',
  author = 'Alexander Rush',
  author_email = 'srush@csail.mit.edu',
  url = 'https://github.com/srush/pydecode/',
  download_url = 'https://github.com/srush/PyDecode/tarball/master',
  keywords = ['nlp'], # arbitrary keywords
  classifiers = []
)
