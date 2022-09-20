#!/bin/bash

################################################################################
#                                   LICENSE                                    #
################################################################################
#   This file is part of libtmpl.                                              #
#                                                                              #
#   libtmpl is free software: you can redistribute it and/or modify            #
#   it under the terms of the GNU General Public License as published by       #
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
#   Author:     Ryan Maguire                                                   #
#   Date:       September 19, 2022                                             #
################################################################################

# Choose whatever C compiler you want. Tested with gcc, clang, tcc, and pcc
# on GNU/Linux (Debian, Ubuntu, Fedora, and more) and FreeBSD 12.1.
CC=cc

# Same thing with the assembly. Tested with GCC and clang.
ASM=cc

# Version of C to be used. Change this with -std=cxx.
STDVER=""

# Use of OpenMP, the multiprocessing API. Enable this with -omp.
USEOMP=1

# Use inline code for small functions (like absolute value). Can give a speed
# boost, but makes that compiled library file a tiny bit bigger. Only works
# with compilers supporting C99 (or higher) or the GNU inline extension.
# Enable this with -inline.
USEINLINE=0

# Whether or not to use libtmpl's implementation of libm.
USEMATH=1

# Use of the IEEE-754 floating point format.
USEIEEE=1

# Files to be excluded (added later based on USEINLINE and USEMATH.
Exclude=""

# You can pass extra arguments. Just add -MyArgument.
ExtraArgs=""

# Parse the inputs.
for arg in "$@"; do

    # If there are no more arguments, break out of this loop.
    if [ "$arg" == "" ]; then
        break

    # Check if the user wants to use a different compiler.
    elif [[ "$arg" == *"-cc"* ]]; then
        CC=${arg#*=}

        elif [[ "$arg" == *"-asm"* ]]; then
        ASM=${arg#*=}

    # Check if the user wants to use a different version of the C language.
    elif [[ "$arg" == *"-std"* ]]; then
        STDVER=$arg

    # Check if OpenMP support is requested.
    elif [ "$arg" == "-omp" ]; then
        USEOMP=1

    # Check if the user wants to inline small functions.
    elif [ "$arg" == "-inline" ]; then
        USEINLINE=1

    elif [ "$arg" == "-nomath" ]; then
        USEMATH=0

    elif [ "$arg" == "-noieee" ]; then
        USEIEEE=0

    # Check for any extra arguments.
    else
        ExtraArgs="$ExtraArgs ${arg#*=}"
    fi
done

# Check for incompatible requests. inline can't be used with -std=c89/c90.
if [ $USEINLINE == 1 ]; then
    if [ "$STDVER" == "-std=c89" ]; then
        echo "Error: inline mode cannot be used with C89."
        echo "       Set -std to a version supporting inline."
        exit 1
    elif [ "$STDVER" == "-std=c90" ]; then
        echo "Error: inline mode cannot be used with C90."
        echo "       Set -std to a version supporting inline."
        exit 1
    fi
fi

# If OpenMP support is requested, add this to the extra arguments.
if [ $USEOMP == 1 ]; then
    ExtraArgs="$ExtraArgs -fopenmp"
fi

# LLVM's clang has the -Weverything warning which enables every possible
# warning. Padding warning's are unnecessary, as are warnings about comparing
# floats for equality. All other warnings should be enabled.
if [ "$CC" == "clang" ]; then
    ExtraArgs="$ExtraArgs -Weverything -Wno-padded -Wno-float-equal"
fi

if [ $USEMATH == 1 ]; then
    ExtraArgs="$ExtraArgs -DTMPL_SET_USE_MATH_TRUE"
fi

if [ $USEIEEE == 0 ]; then
    ExtraArgs="$ExtraArgs -DTMPL_SET_TMPL_USE_IEEE_FALSE"
fi

if [ $USEINLINE == 1 ]; then
    ExtraArgs="$ExtraArgs -DTMPL_SET_INLINE_TRUE"
fi

CompilerArgs="-Wall -Wextra -Wpedantic -fopenmp -I../ -O3 -fPIC -flto -DNDEBUG"
CompilerArgs="$CompilerArgs $ExtraArgs"

# Header file that needs to be created prior to building libtmpl.
CONFIG_HEADER=include/tmpl_config.h

# C file for creating this header.
CONFIG_FILE=config.c

# Name of the executable to create this header.
CONFIG_EXEC=config.out

# There may be left-over .so and .o files from a previous build. Remove those
# to avoid a faulty build.
echo "Clearing older files"
rm -f *.so *.o *.obj *.lib monster.c

# If the config header already exists, remove it.
if [ -e "$CONFIG_HEADER" ]; then
    rm -f "$CONFIG_HEADER";
fi

# Create the config header.
echo "Creating $CONFIG_HEADER"
$CC $STDVER $ExtraArgs $CONFIG_FILE -o $CONFIG_EXEC
./$CONFIG_EXEC
rm -f $CONFIG_EXEC

touch monster.c

Exclude="$Exclude tmpl_sqrt_double.c"
Exclude="$Exclude tmpl_sqrt_float.c"
Exclude="$Exclude tmpl_sqrt_ldouble.c"

for file in include/*.h; do
    echo "#include \"$file\"" >> monster.c;
done

for dir in src/*/; do
    for filename in $dir*.c; do
    	filename_without_path=$(basename -- $filename)
        if [[ $Exclude == *"$filename_without_path"* ]]; then
            continue;
        fi
        echo "#include \"$filename\"" >> monster.c;
    done
done

echo "Compiling libtmpl..."
$CC $CompilerArgs -c monster.c -o monster.o
$ASM $CompilerArgs -c src/math/tmpl_sqrt_double_x86_64.S
$ASM $CompilerArgs -c src/math/tmpl_sqrt_float_x86_64.S
$ASM $CompilerArgs -c src/math/tmpl_sqrt_ldouble_x86_64.S
$CC -fopenmp -O3 -flto -shared -lm *.o -o libtmpl.so
rm -f *.o
rm -f monster.c
echo "Done"
