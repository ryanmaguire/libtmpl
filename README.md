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
Options to pass to `make`

`OMP=1`
> Compile with `OpenMP` support (highly recommended). **WARNING**
> Apple's version of clang does **NOT** support OpenMP, and the `-fopenmp`
> option will result in an error. Homebrew has versions of clang and gcc that
> do support OpenMP.

`NO_INLINE=1`
> Do not use any inline code. This results in a slightly
> smaller `libtmpl.so` file, but several functions become significantly
> slower (not recommended). If your compiler does not support `C99` or higher,
> and does not support the `gcc` `inline` extension, enable this option.

`NO_MATH=1`
> Do not use `libtmpl`'s implementation of `libm`, the C
> standard library for mathematical tools, instead using your compilers
> implementation. This may be recommended. Tests against `glibc`,
> `FreeBSD libc`, and `MSVC`'s implementation of `libm` show that
> `libtmpl` can be significantly faster (all functions have benchmarks in the
> `tests/` directory and you may see for yourself), but this has only been
> tested on the architectures supported by the Debian GNU/Linux operating
> system. Users of other architectures may wish to use their default `libm`.
> Also, if your compiler does not support the `IEEE-754` standard (most do),
> or does not support type-punning for `union`, the portable algorithms
> (algorithms that do not use `IEEE-754` or type-punning) are much slower. In
> these instances you may wish to use the default `libm`.

`NO_IEEE=1`
> Disable use of the `IEEE` formats for `float` and `double`. The `config.c`
> file should detect if your compiler supports this, and type-punning for
> `union`, so you should not need to set this option manually
> (not recommended).

`NO_ASM=1`
> Only applicable is `NO_MATH` is not set, and for `x86_64/amd64/arm64/armv7l`
> machines. Some functions, like `sqrt`, can be handle efficiently in assembly
> code. If you wish to use only C code, set this option (not recommended).

`NO_BUILTIN=1`
> Only applicable is `NO_MATH` and `NO_ASM` are not set, and only for
> `x86_64/amd64/arm64` machines. If you are using `gcc`, `clang`, or `pcc`,
> you can take adventage of several built-in functions like `sincos`. This is
> handled in assembly code. If you're not using a compiler that has
> these built-in functions, set this option (not recommended).

`FASM=1`
> Use the flat assembler instead of the assembly language used by `gcc` and
> `clang`. You must have `fasm` installed to use this. This option is ignored
> if `NO_ASM=1` is set.

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

## Installation using CMake

### Prerequisites
#### Install Conan
Dependencies for libtmpl are provided using the [Conan](https://conan.io/) package manager. The simplest means to install Conan is to use Python's `pip` package mananger:
```shell
pip install conan
```
with only Python >= 3.6 supported. For installation by other means, please see [these instrucctions](https://docs.conan.io/en/latest/installation.html#).

After installing Conan, generate the default profile with
```shell
conan profile new default --detect
```
#### Install CMake
Please download and install the latest version of CMake from [here](https://cmake.org/download/).

#### [Optional] Ninja
CMake can generate Ninja build files, which can result in a more performant build. The simplest way to install
Ninja is to use the pre-built packages via a package manager. For example, using Debian's apt-get

```shell
apt-get install ninja-build
```

or using Python's pip package manager
```shell
pip install ninja
```
. For other package managers, please see [this page](https://github.com/ninja-build/ninja/wiki/Pre-built-Ninja-packages).

### CMake options
`LIBTMPL_USE_OMP:BOOL`
> Compile with `OpenMP` support (highly recommended).
**WARNING** Apple's version of clang does **NOT** support OpenMP, and the `-fopenmp` option will result in an error.
Homebrew has versions of clang and gcc that do support OpenMP."

`LIBTMPL_USE_INLINE:BOOL`
> Use inline code. If disabled, this results in a slightly smaller `libtmpl.so` file, but several
functions become significantly slower (not recommended). If your compiler does not support `C99` or higher, and
does not support the `gcc` `inline` extension, set this option to FALSE.

`LIBTMPL_USE_MATH:BOOL`
> Use `libtmpl`'s implementation of `libm`, the C standard library for mathematical tools,
instead using your compiler's implementation. This may be recommended. Tests against `glibc`, `FreeBSD libc`, and
`MSVC`'s implementation of `libm` show that `libtmpl` can be significantly faster (all functions have benchmarks
in the `tests/` directory and you may see for yourself), but this has only been tested on the architectures supported
by the Debian GNU/Linux operating system. Users of other architectures may wish to use their default `libm`. Also, if
your compiler does not support the `IEEE-754` standard (most do), or does not support type-punning for `union`, the
portable algorithms (algorithms that do not use `IEEE-754` or type-punning) are much slower. In these instances you
may wish to use the default `libm`.

`LIBTMPL_USE_IEEE: BOOL`
> Enable use of the `IEEE` formats for `float` and `double`. The `config.c` file should detect if your
compiler supports this, and type-punning for `union`, so you should not need to set this option manually
(not recommended).

`LIBTMPL_USE_ASM:BOOL`
> Only applicable is `LIBTMPL_USE_MATH` is FALSE, and for `x86_64/amd64/arm64/armv7l` machines. Some functions,
like `sqrt`, can be handle efficiently in assembly code. If you wish to use only C code, set this option to FALSE
(not recommended).

`LIBTMPL_USE_BUILTIN:BOOL`
> Only applicable is `LIBTMPL_USE_MATH` and `LIBTMPL_USE_ASM` are TRUE, and only for `x86_64/amd64/arm64` machines.
If you are using `gcc`, `clang`, or `pcc`, you can take adventage of several built-in functions like `sincos`.
This is handled in assembly code. If you're not using a compiler that has these built-in functions, set this option to
FALSE (not recommended).

`LIBTMPL_USE_FASM:BOOL`
> Use the flat assembler instead of the assembly language used by `gcc` and `clang`. You must have `fasm`
installed to use this. This option is ignored if `LIBTMPL_USE_ASM` is FALSE.

`LIBTMPL_BUILD_TESTS:BOOL`
> Set to TRUE to enable the building of tests.

`LIBTMPL_BUILD_EXAMPLES:BOOL`
> Set to TRUE to enable the building of examples.

`LIBTMPL_STDVER:STRING`
> Set the desired C version by setting to `-std=<version>`, where c89, c90, c99, c11 and c17 are recognized values for
> `<version>`.

### Running CMake
Builds via CMake execute in over a couple of separate stages. The first (the configure/generate) step
is traditionally executed with the follow where CMake cache variables (e.g. the options outlined above)
can be set using `-D<option name>=<value>`.
```shell
cmake -B ../build -S . -DCMAKE_BUILD_TYPE=Debug
```
This command generates the build system using the default generator (i.e. Unix Makefiles on Linux/macOS and Visual Studio project files for Windows) configured for a `Debug`
build. The build system files will be located a `../build`.

To next step is the build stage, which will execute build
```shell
cmake --build ../build
```
And lastly the install stage can be executed with
```shell
cmake --install .../build --prefix=<your install path>
```
which will install the build products at `<your install path>`.

Alternatively, CMake has introduced a [presets syntax](https://cmake.org/cmake/help/latest/manual/cmake-presets.7.html) that allows one to express the desired configure/build options
in a `*.json` file (see CMakePresets.json for the presets used with the Github CI).

To begin, list the available configure presets with
```shell
cmake --list-presets
```

. To execute the configure stage with a preset use
```shell
cmake --preset <configure preset name>
```

. Next, list the available build presets with
```shell
cmake --build --list-presets
```
. Lastly execute the build stage with
```shell
cmake --build --preset <build preset name>
```
.

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
