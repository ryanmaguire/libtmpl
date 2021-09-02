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
        Ryan Maguire, Dartmouth College
--->

# Table of Contents
1. [libtmpl](#libtmpl)
    1. [The Mathematicians Programming Library](#TheMathProgLib)
    2. [Installation (Unix-Like)](#InstallUnix)
    3. [Installation (Window)](#InstallWindows)
2. [tmpyl (Python Wrapper)](#tmpyl)
    1. [Installation](#InstallUnixtmpyl)
3. [tmppl (C++ Wrapper)](#tmppl)
4. [Acknowledgment](#Acknowledgment)
5. [License](#license)

# libtmpl

**This project is still in its infancy and is updated regularly.**

**This library is still being ported over from rss_ringoccs and others.**

The code was scattered across several projects of mine, and this is an attempt
to centralize all of it.

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

The library is split into the following sublibraries:

### bytes
Tools for working with endianness and reading binary files. This code
originated out of the need to read the RSR data files from the Cassini Radio
Science mission, which had big-endianness, on little-endian machines.

### complex
Data types and functions for performing complex arithmetic are given. While
complex.h was included in C99 (and made optional in C11 and C18), it is not
included in C89/C90. This sublibrary provides all of the functions in C99 but
for the C89 user. The code is forward compatible and compiles on C99 and C11
compilers.

### Euclidean planar geometry
2D planar geometry routines. This include typedef's for 2D vectors and matrices.
Linear algebra routines for working with 2x2 matrices are also provided. This
sublibrary is used a lot in the `svg` sublibrary, which is useful for drawing
mathematical figures.

### Euclidean spatial geometry
3D spatial geometry routines. This includes typedef's for 3D vectors and
matrices. Linear algebra routines for working with 3x3 matrices are also
provided. This sublibrary is used in combination with the spherical geometry
routines to provide some non-Euclidean geometry tools.

### fft
Implementations of the standard Fast Fourier Transform algorithms. This includes
the Tukey-Cooley algorithm for data sets that are a power of 2 in size, and the
and Bluestein FFT algorithms for arbitrary sizes. Real and complex inputs are
allowed, the output is always complex valued. Convolutions are also provided.

### graph theory
Currently a limited library that allows one to create bipartite and complete
graphs. This will grow over time.

### ieee754
A library for working with the IEEE754 floating point format. Users most likely
need not delve into these functions, unless they want to learn how the format
works. If your compiler does not use the IEEE754 format, these functions are
most likely useless.

### interpolate
Linear and cubic splining interpolation tools for working with data.

### knots
Tools for working with knot theory, including computing knot invariants, and
working with virtual knots and virtual links. Knots are implemented in a C
struct that represents extended Gauss code.

### math
A collection of functions for running day-to-day math routines, including the
ones in the standard C math library. This is not to replace them, but rather to
show how algorithms are implemented and for the sake of learning. For those with
IEEE754 compliant compilers (which I believe is most in modern times), you'll
find the implemented algorithms are on-par with the glibc (GNU's C library)
math.h functions in terms of computation time and accuracy.

Apart from standard math functions, non-standard functions that are not
included in the C89/C90 math.h header file are defined. Functions like the
hyperbolic trig functions, error functions, and more are defined.

### number theory
Basic functions for working with integers. This includes the binary
GCD algorithms for efficient GCD computation, computation of Bezout
coefficients, and tools for working with prime numbers.

### numerical
A bunch of numerical algorithms for differentiation and integration. This
includes 5 point numerical derivatives, implementations of Halley's and
Newton's method, and more.

### optics
Functions commonly used in geometric optics. There are also functions for
working with Fourier optics, in particular Fraunhofer and Fresnel optics.

### polynomial
Provides tools for working with polynomials over the integer (Z), the
rationals (Q), the reals (R), and the complex numbers (C). Also provides tools
for working with Laurent polynomials ("polynomials" with negative exponents
allowed).

### special_functions
A plethora of special functions that arise in physics and mathematics, from
Bessel functions, to Lambert's W function, and more. Real and complex versions
are given. The algorithms are simple, but fast, usually relying on a combination
of Taylor series for certain values and asymptotic expansions for others.

### vector
Tools for working with vectors, including vector arithmetic, and basic vector
functions. Basic matrix tools and typedef's.

### linear_algebra
Combines the matrix and vector sublibraries together with a bunch of other tools
to perform common operations from linear algebra. This include less common 
operations like Moore-Penrose pseudo inverses. Such tools are useful for filter
applications, such as the Savitzky-Golay smoothing filter.

### string
Provides basic string manipulations that are defined in the POSIX version of C,
but are not part of the C standard. This includes the strdup function. The
phrase "tmpl" is preprended to all functions to avoid name conflicts.

### Wish List
Abstract algebra (groups), topology.

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
The inplace method will place libtmpl.so in `libtmpl/`. You will NOT have
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
**After running `make`, source your `.bashrc` file:**
```
source ~/.bashrc
```

### Some Warnings
Apple's version of clang does **NOT** support OpenMP, and the `-fopenmp` option
will result in an error. Homebrew has versions of clang and gcc that do support
OpenMP.

On Debian GNU/Linux 10 (Buster), there are two problems with PCC and TCC.
The version of TCC (the Tiny C Compiler) that ships with Debian 10 does not
accept 0.0 * HUGE_VAL as a compiler-time constant. This value is used to
represent Not-A-Number. On Debian 11 (Bullseye), the more up-to-date version of
TCC correctly compiles libtmpl.

On PCC (the Portable C Compiler), it fails to compile because it cannot
handle glibc's math.h. In particular, it complains about certain typedef's
in `bits/floatn.h`. In Debian 11 (Bullseye), the more recent version of PCC
compiles libtmpl without error.

In both cases, the problem does not seem to be with libtmpl, but with the
particular versions of those compilers. At any rate, clang and gcc compile
without error, and without warnings :)

## Installation (Windows) <a name="InstallWindows"></a>
Step 1: Remove Windows and install a nice Linux distribution. I recommend
Debian for the more tech-savvy, and Pop!_OS for those who never want to
use a terminal.

Step 2: If you insist on using Windows, try the following. I ran this in a
virtual machine and it worked. I tried writing a powershell script, but after
many failed attempts I gave up. This works, so here ya go.
You can use LLVM's clang with clang-cl or Microsoft's MSVC. I also had some
success using Cygwin to emulate Unix-like commands in Windows.

```
# Remove old files.
del *.exe *.obj *.o *.so *.dll

# Create the tmpl_endianness.h header file. Using MSVC
cl det_end.c /link /out:det.exe

# Using clang
clang-cl det_end.c -o det.exe

# Run the executable.
det.exe
del det.exe

# Create the rest of the library. Using Microsoft's C Compiler:
for /D %d in (.\src\*) do cl /I../ /O2 /c .\src\%d\*.c

# Using LLVM's clang
for /D %d in (.\src\*) do clang-cl -O2 -I../ -c .\src\%d\*.c

# Link and create a .dll file. Using MSVC:
cl .\*.obj /LD /O2 /out:libtmpl.dll

# Using clang
clang-cl .\*.obj -O2 -flto -shared -o -libtmpl.dll

# Remove old stuff.
del *.exe *.obj
```
This creates libtmpl.dll directly in the top directory of libtmpl. You can
move this to the `System32` directory, or add this directory to your path.

The other option is using the Linux Subsystem for Windows. I've not personally
tried this, but a colleague has had some success with it.

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

# Acknowledgment
Thanks must be paid to Peter Doyle and Vladimir Chernov (Dartmouth College) for
many conversations about virtual knots and discussing how to implement
algorithms. Richard French (Wellesley College) was instrumental in getting this
project going and helped with a lot of the optics code. And James "Kiwi"
Graham-Eagle (UMass Lowell) helped with the special-functions algorithms.

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

