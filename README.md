# libtmpl

## Installation
Simply run the Makefile with:
```
make
```
Note, this requires sudo privileges. This has been tested on various GNU/Linux
distributions, macOS, and FreeBSD. I tried to make an nmake file for Windows
users, but gave up. I may return to this eventually.

There is also `make.sh` which is a shell script written in bash that has the
same functionality as `Makefile` except that various pedantic compiler options
are passed to the compiler. This is to ensure as best as possible that the code
is written in strictly compliant C89/C90 code. This has been tested with several
compilers, including GCC (GNU), Clang (LLVM), TCC (Tiny C Compiler), and
PCC (Portable C Compiler).

## The Mathematicians Programming Library
This project is a collection of code written in C89/C90 (commonly called ANSI C)
for mathematicians and physicists to use on various types of projects. It
started with rss_ringoccs, a suite of tools written for processing the Cassini
radio science data, which is written mostly in C (but also Python), but
eventually grew beyond the scope of just astronomy. **This project is still in
its infancy** and is updated regularly. The current goal is have the following
sublibraries included in libtmpl:

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

## special_functions
A plethora of special functions that arise in physics and mathematics, from
Bessel functions, to Lambert's W function, and more. Real and complex versions
are given. The algorithms are simple, but fast, usually relying on a combination
of Taylor series for certain values and asymptotic expansions for others.

## geometry
Basic 2D and 3D Euclidean geometry.

## matrix
Basic matrix tools and typedef's.

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
Graph theory, abstract algebra (groups), topology, knot theory.

# NOTE:
**This library is still being ported over from rss_ringoccs and others.** The
code was scattered across several projects of mine, and this is an attempt to
centralize all of it.

