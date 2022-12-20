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
2. [Language Bindings (C++, Python, IDL)](#bindings)
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

The ``examples/`` folder contains examples of all of the functions in the
library and shows basic usage of these tools.

The ``tests/`` folder contains time and accuracy tests of ``libtmpl`` against
other libraries. To run these tests will require these libraries being
available. Running these tests is **not** required, and they are mostly for
internal use and to verify the algorithms implemented in libtmpl.

## Installation (GNU, Linux, FreeBSD, macOS) <a name="InstallUnix"></a>
Run the Makefile with (`FreeBSD` users should use `gmake`):
```
make
```
The Makefile is parallelizable which saves quite a bit of time, especially on
emulated architectures:
```
make -j
```
Options to pass to `make`:

`OMP=1`
> Compile with `OpenMP` support. **WARNING** Apple's version of clang does
> **NOT** support OpenMP, and the `-fopenmp` option will result in an error.
> Homebrew has versions of clang and gcc that do support OpenMP. This option is
> particularly recommended if you will be doing a lot of computations with
> special functions in Python using the `tmpyl` library and have a CPU with a
> decent number of cores.

`NO_INLINE=1`
> Do not use any inline code. This may (pending other options) result in a
> smaller `libtmpl.so` file, but several functions become significantly
> slower (not recommended). If your compiler does not support `C99` or higher,
> and does not support the `gcc` `inline` extension, enable this option.

`NO_MATH=1`
> Do not use `libtmpl`'s implementation of `libm`, the C
> standard library for mathematical tools, instead using your compilers
> implementation. This may be recommended. Tests against `glibc`,
> `FreeBSD libc`, and `MSVC`'s implementation of `libm` show that
> `libtmpl` can be significantly faster while achieving 1 ULP in error
> (all functions have benchmarks in the `tests/` directory and you may
> see for yourself), but this has only been
> tested on the architectures supported by the Debian GNU/Linux operating
> system (`amd64/x86_64`, `i386`, `aarch64/arm64`, `armhf`, `armel`, `mipsel`,
>`mips`, `mips64el`, `ppc64el`, `powerpc`, `s390x`, `alpha`,
> `riscv`, `sh4`, `sparc`). All architectures other than `amd64/x86_64` and
> `aarch64/arm64` were emulated using `debootstrap` + `chroot` with `QEMU`.
> Time-tests show `libtmpl` performs well on these architectures, but results
> may not be indicative of actual hardware. Users of architectures not listed
> may wish to use their default `libm`.
> Also, if your compiler does not support the `IEEE-754` standard (most do),
> or does not support type-punning for `union`, the portable algorithms
> (algorithms that do not use `IEEE-754` or type-punning) are much slower. In
> these instances you may wish to use the default `libm`.

`NO_INT=1`
> A few functions (like `tmpl_Double_Mod_2`) can get significant performance
> boosts if 32-bit and 64-bit fixed width integers are available. This is
> not required by the C language, however, and the types
> `uint64_t` and `uint32_t` are not required to be defined in `stdint.h`, even
> for C99 compliant compilers (but these types usually are, in practice). The
> `config.c` file will attempt to detect these integer sizes in a C89
> compatible manner by examining the macros in `limits.h`. If you wish to
> skip all of this (not recommended), enable this option. The alternative
> algorithms use manipulations of the bit-fields that represent 32-bit
> `float` and 64-bit `double`, rather than type-punning 32-bit and 64-bit
> integers.

`NO_LONGLONG=1`
> Skip `long long` functions. If your compiler supports C99 or higher, the
> `long long` type is available. In certain environments (most modern machines
> running GNU/Linux, FreeBSD, or macOS) `long long` and `long` are identical,
> meaning it is somewhat wasteful to have two versions of the same function.
> Enable this option if you only wish to use `long` functions.

`NO_IEEE=1`
> Disable use of the `IEEE` formats for `float` and `double`. The `config.c`
> file should detect if your compiler supports this, and type-punning for
> `union`, so you should not need to set this option manually
> (not recommended).

`NO_ASM=1`
> Only applicable if `NO_MATH` is not set, and for `x86_64/amd64`, `i386`,
> `arm64/aarch64`, and `armv7l` machines. Some functions, like `sqrt`, can be
> handled efficiently in assembly code. If you wish to use only C code,
> set this option (not recommended).

`FASM=1`
> Use the flat assembler instead of the assembly language used by `gcc` and
> `clang`. You must have `fasm` installed to use this. This option is ignored
> if `NO_ASM=1` is set. Only applicable on `x86_64/amd64` machines.

`CC=cc`
> The C compiler you use. On Debian GNU/Linux and derivatives (Ubuntu, etc.)
> `gcc`, `clang`, `tcc`, and `pcc` have all been tested and work as expected.
> For `tcc` you **MUST** either pass the `NO_ASM=1` option since this compiler
> (as of this writing) does not support assembly language, or use
> `FASM=1` if you have `fasm` installed.

`EXTRA_FLAGS=`
> Any extra compiler flags you wish to pass. For example, with `CC=clang` you
> can pass `EXTRA_FLAGS="-Weverything -Wno-padded -Wno-float-equal"` to see if
> `libtmpl` builds with all flags (except `-Wpadded` and `-Wfloat-equal`)
> enabled.

`ARCH=`
> Manually set the name of the architecture you are using. The Makefile
> attempts to detect your architecture via the `uname -m` unix command. This
> will most likely work for you. The sole exception I came across is
> emulating an `i386` machine on an `x86_64/amd64` host. The result of
> `uname -m` is `x86_64`, even though the emulated architecture is `i386`. As
> a result the wrong assembly code is used and the compiling fails. Set
> `ARCH=i386` to manually override this if you're in a similar situation.
> (Note: Emulating `aarch64`, `mips`, `powerpc`, etc. on an `x86_64` host
> works fine without the need to set this option).

Afterwords, if you would like to install libtmpl in `/usr/local/lib`, run:
```
sudo make install
```
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

## Installation (Windows) <a name="InstallWindows"></a>
Run the batch script `make.bat`.
```
C:\Users\ryan\source\repos\libtmpl>make.bat
```
This creates libtmpl.lib in the `libtmpl/` directory.
It does not copy the `include/` directory or the library to any system
directories. This has been tested using a Windows 10 virtual machine and it
worked as expected.

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
