#!/bin/bash

################################################################################
#                                  LICENSE                                     #
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
#   Date:       March 10, 2021                                                 #
################################################################################

# This file is for developers and internal use. It has many pedantic compiler
# arguments to ensure libtmpl is written in strict ANSI compliant C code. It
# also has debugging options. The Makefile can be used for most purposes, simply
# by typing make in libtmpl/. This file can also be used via ./make.sh. Both the
# shell script and Makefile have similar functionality, and will build a working
# version of libtmpl, the difference being that the Makefile lacks all of the
# warning compiler options.

# Choose whatever C compiler you want. Tested with gcc, clang, tcc, and pcc
# on GNU/Linux (Debian, Ubuntu, Fedora, and more) and FreeBSD 12.1.
CC=cc
STDVER="-std=c89"
USEOMP=0
INPLACE=0
ExtraArgs=""

for arg in "$@"; do
    if [ "$arg" == "" ]; then
        break
    elif [[ "$arg" == *"-cc"* ]]; then
        CC=${arg#*=}
    elif [[ "$arg" == *"-std"* ]]; then
        STDVER=$arg
    elif [ "$arg" == "-omp" ]; then
        USEOMP=1
    elif [ "$arg" == "-inplace" ]; then
        INPLACE=1
    else
        ExtraArgs="$ExtraArgs ${arg#*=}"
    fi
done

if [ $USEOMP == 1 ]; then
    ExtraArgs="$ExtraArgs -fopenmp"
fi

# Name of the created Shared Object file (.so).
SONAME="libtmpl.so"

# Location to store SONAME at the end of building.
SODIR="/usr/local/lib"

# Compiler arguments. All of these are supported by gcc, tcc, pcc, and clang.
CArgs1="-pedantic -Wall -Wextra -Wpedantic -Wmissing-field-initializers"
CArgs2="-Wconversion -Wmissing-prototypes -Wmissing-declarations"
CArgs3="-Winit-self -Wnull-dereference -Wwrite-strings -Wdouble-promotion"
CArgs4="-Wfloat-conversion -Wstrict-prototypes -Wold-style-definition"
CArgs5="-I../ -DNDEBUG -g -fPIC -O3 -flto -c"
CompilerArgs="$STDVER $ExtraArgs $CArgs1 $CArgs2 $CArgs3 $CArgs4 $CArgs5"

# Linking arguments.
# -O3 is optimization level 3.
# -I../ means include the parent directory so libtmpl/ is in the path.
# -flto is link time optimization.
# -lm means link against the standard math library.
# -o means create an output.
# -shared means the output is a shared object, like a library file.
if [ $USEOMP == 1 ]; then
    LinkerArgs="-O3 -I../ -flto -fopenmp -shared -o $SONAME -lm"
else
    LinkerArgs="-O3 -I../ -flto -shared -o $SONAME -lm"
fi

# Location where the .h files will be stored.
INCLUDE_TARGET=/usr/local/include/libtmpl

# Name of the header file containing endianness info. We need to create this.
END_HEADER=./include/tmpl_endianness.h

# C file for determining endianness and creating END_HEADER.
DET_END_FILE=./det_end.c

# Name of the executable create by DET_END_FILE.
DET_END_EXEC=det_end_out

# There may be left-over .so and .o files from a previous build. Remove those
# to avoid a faulty build.
echo "Clearing older files..."
rm -f *.so *.o
if [ -e "$END_HEADER" ]; then
    rm -f "$END_HEADER";
fi

if [ $INPLACE == 0 ]; then
    if [ -d "$INCLUDE_TARGET" ]; then
        echo "Clearing $INCLUDE_TARGET..."
        sudo rm -rf "$INCLUDE_TARGET";
    fi

    if [ -e "$SODIR/$SONAME" ]; then
        echo "Erasing $SODIR/$SONAME..."
        sudo rm -f "$SODIR/$SONAME";
    fi
fi

echo "Creating include/tmpl_endianness.h file..."
$CC $DET_END_FILE -o $DET_END_EXEC
./$DET_END_EXEC
rm -f $DET_END_EXEC

if [ $INPLACE == 0 ]; then
    echo "Copying include/ directory to /usr/local/include/libtmpl/..."
    sudo mkdir -p "$INCLUDE_TARGET/include/"
    sudo cp ./include/*.h "$INCLUDE_TARGET/include/"
fi

echo "Compiling libtmpl..."
echo "    Compiler:"
echo "        $CC"
echo "    Version:"
echo "        $STDVER"
echo "    Compiler Options:"
echo "        $CArgs1"
echo "        $CArgs2"
echo "        $CArgs3"
echo "        $CArgs4"
echo "        $CArgs5"
echo "    Extra Compiler Arguments:"
echo "        $ExtraArgs"

# Loop over all directories in src/ and compile all .c files.
for dir in ./src/*; do
    echo ""
    echo "    Compiling $dir"
    for filename in $dir/*.c; do
        echo "        Compiling: $filename"
        if !($CC $CompilerArgs $filename); then
            exit 1
        fi
    done
done

echo ""
echo "Building libtmpl Shared Object (.so file)"
if !($CC ./*.o $LinkerArgs); then
    exit 1
fi

if [ $INPLACE == 0 ]; then
    echo "Moving to /usr/local/lib/libtmpl.so"
    sudo mv $SONAME $SODIR
fi

echo "Cleaning up..."
rm -f *.o

echo "Done"

if [ $INPLACE == 1 ]; then
    echo "PLEASE NOTE:"
    echo "    You used the in-place option."
    echo "    libtmpl was only installed in this directory:"
    echo "        $(pwd)"
    echo "    To use libtmpl you must have this in your path."
    echo "    The header files are located in:"
    echo "        $(pwd)/include/"
    echo "    and have NOT been placed in /usr/local/include/"
    echo "    Your compiler will not see these if you"
    echo "    do not pass the correct options."
    echo "    For most compilers (GCC, Clang, PCC, TCC) you can link"
    echo "    libtmpl to you programs with the proper include"
    echo "    directories using the -I and -L option as follows:"
    echo "        gcc -I$(pwd)/../ -L$(pwd)/ my_file.c -o my_output -ltmpl"
fi
