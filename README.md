# Table of Contents
1. [libtmpl](#libtmpl)
    1. [The Mathematicians Programming Library](#TheMathProgLib)
    2. [Installation (Unix-Like)](#InstallUnix)
    3. [Installation (Window)](#InstallWindows)
    
2. [tmpyl](#tmpyl)
    1. [Installation](#InstallUnixtmpyl)

# libtmpl

## The Mathematicians Programming Library <a name="TheMathProgLib"></a>
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

### complex
Data types and functions for performing complex arithmetic are given. While
complex.h was included in C99 (and made optional in C11 and C18), it is not
included in C89/C90. This sublibrary provides all of the functions in C99 but
for the C89 user. The code is forward compatible and compiles on C99 and C11
compilers.

### bytes
Tools for working with endianness and reading binary files. This code
originated out of the need to read the RSR data files from the Cassini Radio
Science mission, which had big-endianness, on little-endian machines.

### special_functions
A plethora of special functions that arise in physics and mathematics, from
Bessel functions, to Lambert's W function, and more. Real and complex versions
are given. The algorithms are simple, but fast, usually relying on a combination
of Taylor series for certain values and asymptotic expansions for others.

### geometry
Basic 2D and 3D Euclidean geometry.

## matrix
Basic matrix tools and typedef's.

### knots
Tools for working with knot theory, including computing knot invariants, and
working with virtual knots and virtual links.

### graphs
Currently a limited library that allows one to create bipartite and complete
graphs. This will grow over time.

### vector
Tools for working with vectors, including vector arithmetic, and basic vector
functions.

### linear_algebra
Combines the matrix and vector sublibraries together with a bunch of other tools
to perform common operations from linear algebra. This include less common 
operations like Moore-Penrose pseudo inverses. Such tools are useful for filter
applications, such as the Savitzky-Golay smoothing filter.

### numerical
A bunch of numerical algorithms for differentiation and integration.

### interpolate
Linear and cubic splining interpolation tools for working with data.

### string
Provides basic string manipulations that are defined in the POSIX version of C,
but are not part of the C standard. This includes the strdup function. The
phrase "tmpl" is preprended to all functions to avoid name conflicts.

### fft
Tukey-Cooley and Bluestein FFT algorithms for real and complex inputs.
Convolutions are also provided.

### Wish List
Abstract algebra (groups), topology.

## NOTE:
**This library is still being ported over from rss_ringoccs and others.** The
code was scattered across several projects of mine, and this is an attempt to
centralize all of it.

## Installation (GNU, Linux, FreeBSD, macOS) <a name="InstallUnix"></a>
Simply run the Makefile with:
```
make
```
Note, this requires sudo privileges. This has been tested on various GNU/Linux
distributions, macOS, and FreeBSD.

To compile with OpenMP (which is highly recommended since it has huge
computational benefits), run:
```
make omp
```

You'll of course need a compiler that supports OpenMP.

If you do not have sudo privileges, use the inplace option:
```
make inplace
```

And for inplace with omp support
```
make omp_inplace
```

This will place libtmpl.so in this directory. You will NOT have
the header files placed in /usr/local/include/ and you will therefore need to
pass the -I and -L options to your compiler whenever you want to use libtmpl.
You may also need to update the environment variable LD_LIBRARY_PATH. This
needs to have the location of libtmpl.so in it.

There is also `make.sh` which is a shell script written in bash that has the
same functionality as `Makefile` except that various pedantic compiler options
are passed to the compiler. This is to ensure as best as possible that the code
is written in strictly compliant C89/C90 code. This has been tested with several
compilers, including GCC (GNU), Clang (LLVM), TCC (Tiny C Compiler), and
PCC (Portable C Compiler).

### Some Warnings
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

## Installation (GNU, Linux, FreeBSD, macOS) <a name="InstallUnixtmpyl"></a>
The easiest way to install tmpyl is with pip.
Navigate to the `tmpyl` directory of this repository and run:
```
pip install .
```
You can also use python itself. Using python 3:
```
python3 setup.py install
```
Using python 2:
```
python2 setup.py install
```
NOTE you may need sudo priviledges to run this. On macOS you can just run:
```
python setup.py install
```
pip is the preferred method since one can easily uninstall tmpyl with:
```
pip uninstall tmpyl
```
If installed with python, you'll need to manually remove the generated files.
On Unix-like systems (GNU, Linux, FreeBSD, macOS), there is the `build/`
directory, placed in `libtmpl/tmpyl/build`, and there are two files:
```
/usr/local/lib/pythonx.x/tmpyl.*.so
/usr/local/lib/pythonx.x/dist-packages/tmpyl-*.egg-info
```
Where the `x.x` is determined by the Python version, and the `*` is determined
by your computer architecture and operating system. To uninstall, simply remove
these files and the entire `libtmpl/tmpyl/build` directory.

