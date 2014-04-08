from distutils.core import setup
from distutils.extension import Extension
import os.path
import sys

def check_for_cython():
    try:
        from Cython.Compiler.Version import version
        if int(version.split(".")[1]) < 20:
            raise ImportError("Bad version.")

    except ImportError:
        return False
    else:
        return True

class ExtensionWrapper:
    def __init__(self, debug=False, cython=False):
        self.debug = debug
        self.cython = cython

    def make(self, ext_name, pyx_name, cpp_names, extra_objects=[]):

        return Extension(ext_name,
                         [pyx_name] + cpp_names if self.cython else cpp_names,
                         language='c++',
                         extra_compile_args=["-O0"] if self.debug else [],
                         include_dirs=[r'src/', "."],
                        extra_objects=extra_objects)

    def cmdclass(self):
        if self.cython:
            from Cython.Distutils import build_ext
            return {'build_ext': build_ext}
        return {}

def make_extension(wrapper):
    return [
        wrapper.make("pydecode.hypergraph",
                     "python/pydecode/hypergraph.pyx",
                     ["src/Hypergraph/Hypergraph.cpp",
                      "src/Hypergraph/Map.cpp"]),

        wrapper.make("pydecode.potentials",
                     "python/pydecode/potentials.pyx",
                     ["src/Hypergraph/Semirings.cpp",
                      "src/Hypergraph/SemiringAlgorithms.cpp",
                      "src/Hypergraph/Algorithms.cpp",
                      "src/Hypergraph/Potentials.cpp"],
                     extra_objects = [os.path.abspath('python/pydecode/hypergraph.so')]),

        wrapper.make("pydecode.beam",
                     "python/pydecode/beam.pyx",
                     ["src/Hypergraph/BeamSearch.cpp"],
                     extra_objects=[os.path.abspath('python/pydecode/potentials.so'),
                                    os.path.abspath('python/pydecode/hypergraph.so')])]


def main():
    copy_args = sys.argv[1:]
    has_cython = check_for_cython()
    if '--nocython' in copy_args:
        has_cython = False

    debug = False
    if '--debug' in copy_args:
        debug = True

    wrapper = ExtensionWrapper(cython=has_cython, debug=debug)

    setup(
        name = 'pydecode',
        cmdclass = wrapper.cmdclass(),
        packages=['pydecode'],
        package_dir={'pydecode': 'python/pydecode'},
        ext_modules = make_extension(wrapper),
        requires=["networkx", "pandas"],
        version = '0.1.27',
        description = 'A dynamic programming toolkit',
        author = 'Alexander Rush',
        author_email = 'srush@csail.mit.edu',
        url = 'https://github.com/srush/pydecode/',
        download_url = 'https://github.com/srush/PyDecode/tarball/master',
        keywords = ['nlp'],
        classifiers = [],
        script_args = copy_args
        )

if __name__ == "__main__": main()
