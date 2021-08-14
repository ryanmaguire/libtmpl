#!/bin/bash

# This file is for developers and internal use. It has many pedantic compiler
# arguments to ensure libtmpl is written in strict ANSI compliant C code. It
# also has debugging options. The Makefile can be used for most purposes, simply
# by typing make in libtmpl/. This file can also be used via ./make.sh. Both the
# shell script and Makefile have similar functionality, and will build a working
# version of libtmpl, the difference being that the Makefile lacks all of the
# warning compiler options.

#   Choose whatever C compiler you want. Tested with gcc, clang, tcc, and pcc
#   on GNU/Linux (Debian, Ubuntu, Fedora, and more) and FreeBSD 12.1.
CC=cc
STDVER="-std=c89"
USEOMP=0
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
    else
        ExtraArgs="$ExtraArgs ${arg#*=}"
    fi
done

if [ $USEOMP == 1 ]; then
    ExtraArgs="$ExtraArgs -fopenmp"
fi

# Name of the created Share Object file (.so).
SONAME="libtmpl.so"

# Location to store SONAME at the end of building.
SODIR="/usr/local/lib"

# Compiler arguments.
CArgs1="-pedantic -Wall -Wextra -Wpedantic -Wmissing-field-initializers"
CArgs2="-Wconversion -Wmissing-prototypes -Wmissing-declarations"
CArgs3="-Winit-self -Wnull-dereference -Wwrite-strings -Wdouble-promotion"
CArgs4="-Wfloat-conversion -Wstrict-prototypes -Wold-style-definition"
CArgs5="-I/usr/local/include/ -DNDEBUG -g -fPIC -O3 -flto -c"
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
END_HEADER=include/tmpl_endianness.h

# C file for determining endianness and creating END_HEADER.
DET_END_FILE=./det_end.c

# Name of the executable create by DET_END_FILE.
DET_END_EXEC=det_end_out

#   There may be left-over .so and .o files from a previous build. Remove those
#   to avoid a faulty build.
echo -e "\nClearing older files..."
rm -f *.so *.o
if [ -e "$END_HEADER" ]; then
    rm -f "$END_HEADER";
fi

if [ -d "$INCLUDE_TARGET" ]; then
    sudo rm -rf "$INCLUDE_TARGET";
fi

if [ -d "$SODIR/$SONAME" ]; then
    rm -f "$SODIR/$SONAME";
fi

echo "Creating include/tmpl_endianness.h file..."
$CC $DET_END_FILE -o $DET_END_EXEC
./$DET_END_EXEC
rm -f $DET_END_EXEC

echo "Copying include/ directory to /usr/local/include/libtmpl/"
sudo mkdir -p "$INCLUDE_TARGET/include/"
sudo cp ./include/*.h "$INCLUDE_TARGET/include/"

echo "Compiling libtmpl..."
echo -e "\n\tCompiler:\n\t\t$CC"
echo -e "\n\tVersion:\n\t\t$STDVER"
echo -e "\n\tCompiler Options:"
echo -e "\t\t$CArgs1"
echo -e "\t\t$CArgs2"
echo -e "\t\t$CArgs3"
echo -e "\t\t$CArgs4"
echo -e "\t\t$CArgs5"
echo -e "\n\tExtra Compiler Arguments:\n\t\t$ExtraArgs"

#   Loop over all directories in src/ and compile all .c files.
for dir in ./src/*; do
    echo -e "\n\tCompiling $dir"
    for filename in $dir/*.c; do
        echo -e "\t\tCompiling: $filename"
        if !($CC $CompilerArgs $filename); then
            exit 1
        fi
    done
done

echo -e "\nBuilding libtmpl Shared Object (.so file)"
$CC ./*.o $LinkerArgs

echo "Moving to /usr/local/lib/libtmpl.so"
sudo mv $SONAME $SODIR

LDPATH=/usr/local/lib
if [[ $LD_LIBRARY_PATH == "" ]]; then
    CREATE_NEW_LD_PATH="LD_LIBRARY_PATH=$LDPATH"
    echo -e "\n# Needed for loading libtmpl." >> ~/.bashrc
    echo "$CREATE_NEW_LD_PATH" >> ~/.bashrc
    echo "export LD_LIBRARY_PATH" >> ~/.bashrc
    source ~/.bashrc
elif [[ $LD_LIBRARY_PATH != *"$LDPATH"* ]]; then
    CREATE_NEW_LD_PATH="LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$LDPATH"
    echo -e "\n# Needed for loading libtmpl." >> ~/.bashrc
    echo "$CREATE_NEW_LD_PATH" >> ~/.bashrc
    echo "export LD_LIBRARY_PATH" >> ~/.bashrc
    source ~/.bashrc
fi

echo "Cleaning up..."
rm -f *.o

echo "Done"
