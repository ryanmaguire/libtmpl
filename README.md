# libtmpl

## The Mathematicians Programming Library
This project is a collection of code written in C89/C90 (commonly called ANSI C)
for mathematicians and physicists to use on various types of projects. It
started with rss_ringoccs, a suite of tools written for processing the Cassini
radio science data, which is written mostly in C (but also Python), but
eventually grew beyond the scope of just astronomy. **This project is still in**
**its infancy** and is updated regularly.

**There are no dependencies other than a C compiler and the C standard**
**library.** The library is written entirely in ISO C89/C90 compliant code,
and no C99/C11 or GCC extensions are used. It compiles with C99 and C11/C18
compilers, so it is more fitting to say it is written in the intersection of
these standards. That being said, the ``extras/`` folder contains a plethora of
code for recreational purposes (random walks, fractals, raytracing, and more).
These files are **not** a part of libtmpl and are not compiled via the Makefile
or the ``make.sh`` script, leaving me the freedom to write in whichever language
I please. Still, most of the files in ``extras/`` are in C, but some are in C++,
Python, Sage, and the rare Mathematica file may appear, and some files use C99
tools just to mix it up.

The ``examples/`` folder contains examples of all of the functions in the
library and shows basic usage of these tools. The ``tests/`` folder contains
time tests and accuracy tests of ``libtmpl`` versus other libraries. To run
these tests will require these libraries being available. Running these tests
is **not** required, and they are mostly for internal use and to verify the
algorithms implemented in libtmpl.

The library is split into the following sublibraries:

## math
A collection of functions for running day-to-day math routines, including the
ones in the standard C math library. This is not to replace them, but rather to
show how algorithms are implemented and for the sake of learning. For those with
IEEE754 compliant compilers (which I believe is most in modern times), you'll
find the implemented algorithms are on-par with the glibc (GNU's C library)
math.h functions in terms of computation time and accuracy.

Apart from standard math functions, non-standard functions that are not
included in the C89/C90 math.h header file are defined. Functions like the
hyperbolic trig functions, error functions, and more are defined.

## complex
Data types and functions for performing complex arithmetic are given. While
complex.h was included in C99 (and made optional in C11 and C18), it is not
included in C89/C90. This sublibrary provides all of the functions in C99 but
for the C89 user. The code is forward compatible and compiles on C99 and C11
compilers.

## bytes
Tools for working with endianness and reading binary files. This code
originated out of the need to read the RSR data files from the Cassini Radio
Science mission, which had big-endianness, on little-endian machines.

## special_functions
A plethora of special functions that arise in physics and mathematics, from
Bessel functions, to Lambert's W function, and more. Real and complex versions
are given. The algorithms are simple, but fast, usually relying on a combination
of Taylor series for certain values and asymptotic expansions for others.

## geometry
Basic 2D and 3D Euclidean geometry.

## matrix
Basic matrix tools and typedef's.

## knots
Tools for working with knot theory, including computing knot invariants, and
working with virtual knots and virtual links.

## graphs
Currently a limited library that allows one to create bipartite and complete
graphs. This will grow over time.

## vector
Tools for working with vectors, including vector arithmetic, and basic vector
functions.

## linear_algebra
Combines the matrix and vector sublibraries together with a bunch of other tools
to perform common operations from linear algebra. This include less common 
operations like Moore-Penrose pseudo inverses. Such tools are useful for filter
applications, such as the Savitzky-Golay smoothing filter.

## numerical
A bunch of numerical algorithms for differentiation and integration.

## interpolate
Linear and cubic splining interpolation tools for working with data.

## string
Provides basic string manipulations that are defined in the POSIX version of C,
but are not part of the C standard. This includes the strdup function. The
phrase "tmpl" is preprended to all functions to avoid name conflicts.

## fft
Tukey-Cooley and Bluestein FFT algorithms for real and complex inputs.
Convolutions are also provided.

## Wish List
Abstract algebra (groups), topology.

# NOTE:
**This library is still being ported over from rss_ringoccs and others.** The
code was scattered across several projects of mine, and this is an attempt to
centralize all of it.

## Installation (GNU, Linux, FreeBSD, macOS)
Simply run the Makefile with:
```
make
```
Note, this requires sudo privileges. This has been tested on various GNU/Linux
distributions, macOS, and FreeBSD.

There is also `make.sh` which is a shell script written in bash that has the
same functionality as `Makefile` except that various pedantic compiler options
are passed to the compiler. This is to ensure as best as possible that the code
is written in strictly compliant C89/C90 code. This has been tested with several
compilers, including GCC (GNU), Clang (LLVM), TCC (Tiny C Compiler), and
PCC (Portable C Compiler).

## Installation (Windows)
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
