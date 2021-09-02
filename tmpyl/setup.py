"""
################################################################################
#                                  LICENSE                                     #
################################################################################
#   This file is part of libtmpl.                                              #
#                                                                              #
#   libtmpl is free software: you can redistribute it and/or modify it         #
#   under the terms of the GNU General Public License as published by          #
#   the Free Software Foundation, either version 3 of the License, or          #
#   (at your option) any later version.                                        #
#                                                                              #
#   libtmpl is distributed in the hope that it will be useful,                 #
#   but WITHOUT ANY WARRANTY; without even the implied warranty of             #
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              #
#   GNU General Public License for more details.                               #
#                                                                              #
#   You should have received a copy of the GNU General Public License          #
#   along with libtmpl.  If not, see <https://www.gnu.org/licenses/>.          #
################################################################################
#   Purpose:                                                                   #
#       This file builds tmpyl, the Python Extension module for libtmpl.       #
#       tmpyl is built using the Python-C API and no python code is            #
#       used, other than this setup.py file. Because of this I can only        #
#       guarantee tmpyl will build with CPython. Thatis , I've never tested it #
#       with PyPy or the other implementations of the Python language.         #
#   Notes:                                                                     #
#       tmpyl builds with both Python 2 and Python 3. There are macros inside  #
#       the C source files to check which python version is being used. There  #
#       is also support for numpy arrays. If you do not have numpy installed,  #
#       tmpyl will still build. If you later install numpy, but built tmpyl    #
#       without numpy support, none of the functions will be able to accept    #
#       numpy arrays as arguments. It is highly recommended to build tmpyl     #
#       with numpy support since those tools are very convenient.              #
################################################################################
#   Author: Ryan Maguire                                                       #
#   Date:   August 31, 2021.                                                   #
################################################################################
"""

from distutils.core import setup, Extension
import sys

# ImportError became ModuleNotFoundError in Python 3.6. Check the version first.
if sys.version_info[0] > 2 and sys.version_info[1] > 5:

    # If numpy is not available, we'll specify this with the macro
    # TMPYL_HAS_NUMPY by setting it to zero.
    try:
        import numpy
        include=['../../', numpy.get_include()]
        tmpyl_macros=[("TMPYL_HAS_NUMPY", 1)]
    except ModuleNotFoundError:
        include=['../../']
        tmpyl_macros=[("TMPYL_HAS_NUMPY", 0)]

# For older versions, use ImportError.
else:

    # Again, check if numpy is available.
    try:
        import numpy
        include=['../../', numpy.get_include()]
        tmpyl_macros=[("TMPYL_HAS_NUMPY", 1)]
    except ImportError:
        include=['../../']
        tmpyl_macros=[("TMPYL_HAS_NUMPY", 0)]

# List of files to be compiled for tmpyl.
source_files = [
    "tmpyl.c",
    "tmpyl_common.c",
    "tmpyl_special_functions.c"
]

# Optional arguments for the compiler.
optional_args = [
    "-Wall",
    "-Wextra",
    "-Wconversion"
]

# Create the module.
setup(name='tmpyl',
      version='0.1',
      description='Python Extension module for the C Library libtmpl',
      author='Ryan Maguire',
      ext_modules=[
          Extension('tmpyl',
                    source_files,
                    extra_compile_args=optional_args,
                    define_macros=tmpyl_macros,
                    include_dirs=include,
                    library_dirs=['/usr/local/lib', '../'],
                    libraries=['tmpl'])
          ]
     )
