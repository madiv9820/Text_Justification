from setuptools import setup, Extension
from Cython.Build import cythonize

# 🧩 Define the Cython extension module
ext = Extension(
    name='solution',                    # 📦 Name of the compiled module (import as `solution`)
    sources=['solution.pyx'],           # 📄 Cython source file
    language='c++'                      # ⚙️ Specify C++ (required since we use C++ code)
)

# 🚀 Build configuration
setup(
    ext_modules=cythonize(
        ext,
        language_level=3                # 🐍 Use Python 3 syntax for Cython compilation
    )
)