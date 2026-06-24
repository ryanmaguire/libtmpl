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
    1. [The Mathematicians Programming Library](#intro)
    2. [Installation: Makefile](#Installation-Makefile)
    3. [Installation: Bash Script](#Installation-Bash-Script)
    3. [Installation: Batch Script](#Installation-Batch-Script)
    4. [Directory Structure](#Directory-Structure)
2. [Language Bindings (C++, Python, IDL)](#bindings)
4. [License](#license)

# libtmpl

**This project is still in its infancy and is updated regularly.**

## The Mathematicians Programming Library <a name="intro"/>
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

## Installation: Makefile
Run the Makefile with (`FreeBSD` users should use `gmake`):
```
make
```
The Makefile is parallelizable which saves quite a bit of time, especially on
emulated architectures:
```
make -j
```

Afterwords, if you would like to install libtmpl in `/usr/local/lib`, run:
```
sudo make install
```

The Makefile has many flags that determine how libtmpl is compiled. Use

```
make help
```

to see a description of each command-line option.

**You may need to update the LD_LIBRARY_PATH environment variable.**
Add the following to your `.bashrc`, `.shrc`, or whichever shell you're using.
```
export LD_LIBRARY_PATH="/usr/local/lib:$LD_LIBRARY_PATH"
```
If you did not install libtmpl to `/usr/local/lib`, try:
```
export LD_LIBRARY_PATH="/path/to/libtmpl:$LD_LIBRARY_PATH"
```
To remove all build and `.so` files, run:
```
make clean
```
To uninstall, run:
```
sudo make uninstall
```
To install into a directory tree other than `/usr/local`, set the `prefix`
variable when running `make`, e.g. `make prefix=/opt install`
will install into`/opt/lib` etc.

## Installation: Bash Script
A `bash` script is available, but results in a larger and less performant build.
By default it has nearly all compiler warnings enabled for `gcc` and `clang`
(including `-Weverything` with `clang`) and is used internally as a
quick error check.

To use, run:
```
sudo bash make.sh
```
Options:

`-cc=`
> `C` compiler to be used. Tested with `gcc`, `clang`, `tcc`, and `pcc` on
> Debian GNU/Linux.

`-std=`
> `C` standard to use. Default is `-std=c89`.

`-omp`
> Compile with OpenMP support.

`-inplace`
> Do not install `libtmpl` into `/usr/local/lib/` and `/usr/local/include/`.
> Use this option if you do not have `sudo` privileges.

`-inline`
> Use inline code. You must have `-std` set to `c99` or higher.

`-nomath`
> Do not use `libtmpl`'s implementation of `libm`. Same as `NO_MATH=1` in the
> Makefile.

`-noieee`
> Do not use any type-punning code or code that takes advantage of the
> `IEEE-754` floating point format.

`-noint`
> Do not use any code that uses fixed-width integers.

`-longlong`
> Compile `long long` code. Must have `-std=c99` or higher.

`-monster`
> `libtmpl` was written in a way that allows all `.c` files to be `#include`d
> into one file and then compiled. While this may seem silly, compilers lacking
> link-time optimization can optimize the library at compile time, resulting in
> a very performant build. Astronomical computations performed by `rss_ringoccs`
> are about twice as fast this way. If your compiler has decent link-time
> optimization it makes only a small difference.
> This option creates a single `.c` file that `#include`s the entirety of
> `libtmpl`, appropriately named `monster.c`, and then compiles this.

## Installation: Batch Script
A very primitive batch script exists for Windows users.
Run the script with:
```
C:\Users\ryan\source\repos\libtmpl>make.bat
```
This creates libtmpl.lib in the `libtmpl/` directory.
It does not copy the `include/` directory or the library to any system
directories. This has been tested using a Windows 10 virtual machine and it
worked as expected. It compiles with `MSVC`'s `cl` by default. Pass the option
`clang` or `clang-cl` to use LLVM's `clang` compiler.

## Directory Structure
### data/
Almost all mathematical functions of real or complex variables are
computed via one of two methods:
1. Argument reduction:
> Reduce the input `x` to a small range `[a, b]` and then accurately compute
> the function in the range using some numerical method. Ex: `sin`, `cos`,
> `log`, `sqrt`.

2. Separate argument into windows:
> Determine if the input `x` falls in one of the ranges `[a_0, b_0]`, ...,
> `[a_n, b_n]`, allowing for `a_0 = -inf` and `b_n = +inf`, and then compute
> the function in this range using some numerical method. Ex: `Bessel_J0`,
> `Bessel_I0`. Usually Taylor series for small inputs and asymptotic expansions
> for large.

The numerical methods are typically one of the following:
1. Taylor / Maclaurin Series.
2. Pade Approximants.
3. Asymptotic Expansions.
4. Chebyshev Polynomials.
5. Remez exchange.

Inside ``data/`` lies all of the code for computing the coefficients of these
approximations. None of the code is directly used in `libtmpl`, indeed most
files are in `Python`. This directory is kept in this repository for the sake
of studying algorithms. In particular, for seeing *where* these approximations
come from.

### examples/
All functions have examples of basic usage.

### include/
All header and inline files for `libtmpl`.

### src/
The source files. Mostly `.c`, but a few assembly files are found for certain
architectures.

### tests/
Time and accuracy tests of ``libtmpl`` against other libraries. To run these
tests will require these libraries being available. Running these tests is
**not** required, and they are mostly for internal use and to verify the
algorithms implemented in libtmpl.

# Language Bindings <a name="bindings"></a>
Language bindings, or *wrappers*, are provided for `C++`, `Python`,
and `IDL` (also the Free/Open-Source implementation `GDL`). All bindings require
`libtmpl` being built beforehand. The source codes used to live in this
repository, but have since moved to their own for easier management. These
can be found via the following links.

[C++ (libtmppl)](https://github.com/ryanmaguire/libtmppl)

[Python (libtmpyl)](https://github.com/ryanmaguire/libtmpyl)

[IDL (libtmpidl)](https://github.com/ryanmaguire/libtmpidl)

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
