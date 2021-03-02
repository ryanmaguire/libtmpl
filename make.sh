#!/bin/bash

#   Apple aliases gcc to mean clang. If you have installed gcc via homebrew,
#   version 10, then you can use the following to compile with that. Otherwise,
#   this will compile with clang on mac and gcc on linux.

#   osstring=`uname`
#   if [ "$osstring" = "Darwin" ]; then
#   	CC=gcc-10
#   elif [ "$osstring" = "Linux" ]; then
#   	CC=gcc
#   else
#       echo "Operating System not recognized"
#       echo "Only MacOSX and Linux supported"
#       echo "Exiting script"
#       exit 1
#   fi

#   To make life easy, we'll just use gcc to mean whatever the operating
#   system aliased it as. As stated, for MacOS this is clang, and for linux
#   distribution this is actually gcc. However, you can set this to whichever
#   compiler you want. It should be noted that libtmpl has been tested on
#   clang and gcc on both linux and mac systems using strict compiler options to
#   ensure compliance with the ANSI standard. Changing this to a different
#   compiler "should" work, though it hasn't been tested.
CC=gcc

if [ ! -e "include/tmpl_endianness.h" ]; then
    touch include/tmpl_endianness.h
    $CC -I../ src/bytes/tmpl_determine_endianness.c -c
    $CC det_end.c tmpl_determine_endianness.o -o det_end
    end=`./det_end`
    echo "
/******************************************************************************
 *                                 LICENSE                                    *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify it        *
 *  it under the terms of the GNU General Public License as published by      *
 *  the Free Software Foundation, either version 3 of the License, or         *
 *  (at your option) any later version.                                       *
 *                                                                            *
 *  libtmpl is distributed in the hope that it will be useful,                *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 *  GNU General Public License for more details.                              *
 *                                                                            *
 *  You should have received a copy of the GNU General Public License         *
 *  along with libtmpl.  If not, see <https://www.gnu.org/licenses/>.         *
 ******************************************************************************
 *                              tmpl_endianness                               *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      This file is created by the make.sh file. It provides the macro       *
 *      __TMPL_ENDIANNESS__ which is used in various functions where the code *
 *      is endian specific.                                                   *
 ******************************************************************************/
#ifndef __TMPL_ENDIANNESS_H__
#define __TMPL_ENDIANNESS_H__

#define __TMPL_BIG_ENDIAN__ 0
#define __TMPL_LITTLE_ENDIAN__ 1
#define __TMPL_MIXED_ENDIAN__ 2
#define __TMPL_UNKNOWN_ENDIAN__ 3

#define __TMPL_ENDIAN__ $end

#endif

" >> include/tmpl_endianness.h
    rm -f det_end tmpl_determine_endianness.o
fi

if [ $CC == "gcc" ]; then
    CArgs1="-std=c89 -ansi -pedantic -pedantic-errors -Wall -Wextra -Wpedantic"
    CArgs2="-Wmisleading-indentation -Wmissing-field-initializers -Wconversion"
    CArgs3="-Wmissing-prototypes -Wold-style-definition -Winit-self"
    CArgs4="-Wmissing-declarations -Wnull-dereference -Wwrite-strings"
    CArgs5="-Wdouble-promotion -Wfloat-conversion"
    CArgs6="-Wstrict-prototypes -I../ -DNDEBUG -g -fPIC -O3 -flto -c"
    CompilerArgs="$CArgs1 $CArgs2 $CArgs3 $CArgs4 $CArgs5 $CArgs6"

#   Clang has different compiler options, so specify those here if using clang.
elif [ $CC == "clang" ]; then
    CArgs1="-std=c89 -ansi -pedantic -pedantic-errors -Wall -Wextra -Wpedantic"
    CArgs2="-Wmissing-field-initializers -Wconversion"
    CArgs3="-Wmissing-prototypes -Wold-style-definition -Winit-self"
    CArgs4="-Wmissing-declarations -Wnull-dereference -Wwrite-strings"
    CArgs5="-Wdouble-promotion -Wfloat-conversion"
    CArgs6="-Wstrict-prototypes -I../ -DNDEBUG -g -fPIC -O3 -flto -c"
    CompilerArgs="$CArgs1 $CArgs2 $CArgs3 $CArgs4 $CArgs5 $CArgs6"
elif [ $CC == "tcc" ]; then
    CArgs1="-std=c89 -pedantic -Wall -Wextra -Wpedantic"
    CArgs2="-Wmisleading-indentation -Wmissing-field-initializers -Wconversion"
    CArgs3="-Wmissing-prototypes -Wold-style-definition -Winit-self"
    CArgs4="-Wmissing-declarations -Wnull-dereference -Wwrite-strings"
    CArgs5="-Wdouble-promotion -Wfloat-conversion"
    CArgs6="-Wstrict-prototypes -I../ -DNDEBUG -g -fPIC -O3 -flto -c"
    CompilerArgs="$CArgs1 $CArgs2 $CArgs3 $CArgs4 $CArgs5 $CArgs6"
elif [ $CC == "cc" ]; then
    CArgs1="-std=c89 -pedantic -Wall -Wextra -Wpedantic"
    CArgs2="-Wmisleading-indentation -Wmissing-field-initializers -Wconversion"
    CArgs3="-Wmissing-prototypes -Wold-style-definition -Winit-self"
    CArgs4="-Wmissing-declarations -Wnull-dereference -Wwrite-strings"
    CArgs5="-Wdouble-promotion -Wfloat-conversion"
    CArgs6="-Wstrict-prototypes -I../ -DNDEBUG -g -fPIC -O3 -flto -c"
    CompilerArgs="$CArgs1 $CArgs2 $CArgs3 $CArgs4 $CArgs5 $CArgs6"
fi

echo -e "\nClearing older files..."

#   There may be left-over .so and .o files from a previous build. Remove those
#   to avoid a faulty build.
rm -f *.so *.o

#   The -d option means does-not-have-sudo-support. It is for building libtmpl
#   without super-user/sudo permissions.
if [[ $1 == "-d" ]]; then
    echo "Building in place..."

#   If we have sudo permissions, it is easiest to use libtmpl by placing the
#   header files in /usr/local/include and the compiled shared-object into
#   /usr/local/lib.
else
    echo "Copying include/ directory to /usr/local/include/libtmpl/"
    includedir="/usr/local/include/libtmpl"

    #   Check if /usr/local/include/libtmpl/ is already a directory. If not
    #   then create this via mkdir.
    if [ ! -d "$includedir" ]; then
        sudo mkdir -p "$includedir/include/"
    else

        #   Remove the old header files in case libtmpl has been updated since
        #   the most recent build on your computer.
        sudo rm -f "$includedir/include/*.h"
    fi

    #   Copy the header files to the include directory. This requires sudo
    #   permissions and you will be prompted for a password.
    sudo cp ./include/* "$includedir/include/"
fi

echo "Compiling libtmpl..."
echo -e "\n\tCompiler Options:"
echo -e "\t\t$CArgs1"
echo -e "\t\t$CArgs2"
echo -e "\t\t$CArgs3"
echo -e "\t\t$CArgs4"
echo -e "\t\t$CArgs5"
echo -e "\t\t$CArgs6"

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
sharedobjectlist=""
for filename in ./*.o; do
    sharedobjectlist="$sharedobjectlist $filename"
done

$CC $sharedobjectlist -O3 -flto -shared -o libtmpl.so -lm

if [[ $1 == "-d" ]]; then
    echo "Adding current directory to LD_LIBRARY_PATH..."
    u=$(pwd)
else
    echo "Moving to /usr/local/lib/libtmpl.so"
    sudo mv libtmpl.so /usr/local/lib/libtmpl.so

    echo "Adding /usr/local/lib to LD_LIBRARY_PATH..."
    u=/usr/local/lib
fi

if [[ $LD_LIBRARY_PATH == "" ]]; then
    CREATE_NEW_LD_PATH="LD_LIBRARY_PATH=$u"
    echo -e "\n# Needed for loading libtmpl." >> ~/.bashrc
    echo "$CREATE_NEW_LD_PATH" >> ~/.bashrc
    echo "export LD_LIBRARY_PATH" >> ~/.bashrc
    source ~/.bashrc
elif [[ $LD_LIBRARY_PATH != *"$u"* ]]; then
    CREATE_NEW_LD_PATH="LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$u"
    echo -e "\n# Needed for loading libtmpl." >> ~/.bashrc
    echo "$CREATE_NEW_LD_PATH" >> ~/.bashrc
    echo "export LD_LIBRARY_PATH" >> ~/.bashrc
    source ~/.bashrc
fi

echo "Cleaning up..."
rm -f *.o

echo "Done"