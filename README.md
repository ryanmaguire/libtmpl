<!---
    LICENSE

    This file is part of libtmpl.

    libtmpl is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    libtmpl is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with libtmpl.  If not, see <https://www.gnu.org/licenses/>.

    AUTHOR
        Ryan Maguire
--->

# Table of Contents
1. [libtmpl](#libtmpl)
    1. [The Mathematicians Programming Library](#TheMathProgLib)
    2. [Installation (Unix-Like)](#InstallUnix)
    3. [Installation (Windows)](#InstallWindows)
2. [tmpyl (Python Wrapper)](#tmpyl)
    1. [Installation](#InstallUnixtmpyl)
3. [tmppl (C++ Wrapper)](#tmppl)
4. [License](#license)

# libtmpl

**This project is still in its infancy and is updated regularly.**

## The Mathematicians Programming Library <a name="TheMathProgLib"></a>
This project is a collection of code written in C89/C90 (commonly called ANSI C)
for mathematicians and physicists to use on various types of projects. It
started with rss_ringoccs, a suite of tools written for processing the Cassini
radio science data, which is written mostly in C (but also Python), but
eventually grew beyond the scope of just astronomy.

**There are no dependencies other than a C compiler and the C standard**
**library.** The library is written entirely in ISO C89/C90 compliant code,
and no C99/C11 or GCC extensions are used. It compiles with C99 and C11/C18
compilers, so it is more fitting to say it is written in the intersection of
these standards.

The ``extras/`` folder contains a plethora of code for recreational purposes
(random walks, fractals, raytracing, and more). These files are **not** part
of libtmpl and are not compiled via the Makefile or the ``make.sh`` script.
Most of the files in ``extras/`` are written in C, but some are in C++, Python,
Sage, and the rare Mathematica file may appear, and some files use C99 tools.

The ``examples/`` folder contains examples of all of the functions in the
library and shows basic usage of these tools.

The ``tests/`` folder contains time tests and accuracy tests of ``libtmpl``
versus other libraries. To run these tests will require these libraries being
available. Running these tests is **not** required, and they are mostly for
internal use and to verify the algorithms implemented in libtmpl.

## Installation (GNU, Linux, FreeBSD, macOS) <a name="InstallUnix"></a>
Run the Makefile with (requires sudo privileges):
```
make
```
To compile with OpenMP (highly recommended) run:
```
make omp
```
**If you do not have sudo privileges, use the in-place option**
The in-place method will place libtmpl.so in `libtmpl/`. You will NOT have
the header files placed in `/usr/local/include/` and you will therefore need to
pass the `-I` and `-L` options to your compiler whenever you want to use
libtmpl.
```
make inplace
```
And for inplace with OpenMP support
```
make omp_inplace
```
**You may need to update the LD_LIBRARY_PATH environment variable.**
Add the following to your `.bashrc`, `.shrc`, or whichever shell you're using.
```
export LD_LIBRARY_PATH="/usr/local/lib:$LD_LIBRARY_PATH"
```
If you used the in-place options:
```
export LD_LIBRARY_PATH="/path/to/libtmpl:$LD_LIBRARY_PATH"
```

### Warnings
Apple's version of clang does **NOT** support OpenMP, and the `-fopenmp` option
will result in an error. Homebrew has versions of clang and gcc that do support
OpenMP.

## Installation (Windows) <a name="InstallWindows"></a>
Run the batch script `make.bat`.
```
C:\Users\ryan\source\repos\libtmpl>make.bat
```
This creates libtmpl.lib in the `libtmpl/` directory.
It does not copy the `include/` directory or the library to any system
directories. This has been tested using a Windows 10 virtual machine and it
worked as expected.

# tmpyl
`tmpyl` is a Python Extension module written using the Python-C API. It can be
installed once libtmpl has been built. It is compatible with both Python 2 and
Python 3. If numpy is available, tmpyl can be built with numpy support. This
allows one to pass arrays to libtmpl functions. The `setup.py` script will
determine this for you, and no extra effort is needed.

## Installation <a name="InstallUnixtmpyl"></a>
The easiest way to install tmpyl is with pip.
Navigate to the `tmpyl` directory of this repository and run:
```
pip install .
```
**If you installed libtmpl with the inplace methods, pip will not work.**
You can use python itself. Replace `pythonx` with either `python2`,
`python3`, or `python`, depending on what you have installed.
```
sudo pythonx setup.py install
```
If you lack sudo privileges, run:
```
pythonx setup.py install
```
The `.so` file will be placed in `tmpyl/build/lib/`. Move this file to wherever
you wish, just make sure it is in your `PATH` in order to import `tmpyl`.

# tmppl
`tmppl` is the C++ wrapper for `libtmpl`. There is a Makefile in the
`tmppl/` directory that builds it.

# License
    libtmpl is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    libtmpl is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with libtmpl.  If not, see <https://www.gnu.org/licenses/>.
