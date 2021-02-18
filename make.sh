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

if [ $CC == "gcc" ]; then
    CArgs1="-std=c89 -ansi -pedantic -pedantic-errors -Wall -Wextra"
    CArgs2="-Wpedantic -Wmisleading-indentation -Wmissing-field-initializers"
    CArgs3="-Wmissing-prototypes -Wold-style-definition -Winit-self"
    CArgs4="-Wmissing-declarations -Wnull-dereference -Wwrite-strings"
    CArgs5="-Wconversion -Wdouble-promotion -Wfloat-conversion"
    CArgs6="-Wstrict-prototypes -I../ -DNDEBUG -g -fPIC -O3 -flto -c"
    CompilerArgs="$CArgs1 $CArgs2 $CArgs3 $CArgs4 $CArgs5 $CArgs6"
elif [ $CC == "clang" ]; then
    CArgs1="-std=c89 -ansi -pedantic -pedantic-errors -Wall -Wextra"
    CArgs2="-Wpedantic -Wmissing-field-initializers"
    CArgs3="-Wmissing-prototypes -Wold-style-definition -Winit-self"
    CArgs4="-Wmissing-declarations -Wnull-dereference -Wwrite-strings"
    CArgs5="-Wconversion -Wdouble-promotion -Wfloat-conversion"
    CArgs6="-Wstrict-prototypes -I../ -DNDEBUG -g -fPIC -O3 -flto -c"
    CompilerArgs="$CArgs1 $CArgs2 $CArgs3 $CArgs4 $CArgs5 $CArgs6"
fi

echo -e "\nClearing older files..."
rm -f *.so
rm -f *.o

echo "Copying include/ directory to /usr/local/include/libtmpl/"
includedir="/usr/local/include/libtmpl"

#   Check if /usr/local/include/libtmpl/ is already a directory. If not
#   then create this via mkdir.
[ ! -d "$includedir" ] && sudo mkdir -p "$includedir/include/"
sudo rm -f "$includedir/include/*.h"
sudo cp ./include/* "$includedir/include/"

echo "Compiling libtmpl..."
echo -e "\n\tCompiler Options:"
echo -e "\t\t$CArgs1"
echo -e "\t\t$CArgs2"
echo -e "\t\t$CArgs3"
echo -e "\t\t$CArgs4"
echo -e "\t\t$CArgs5"
echo -e "\t\t$CArgs6"

for dir in ./src/*; do
    echo -e "\n\tCompiling $dir"
    for filename in $dir/*.c; do
        echo -e "\t\tCompiling: $filename"
        $CC $CompilerArgs $filename
    done
done

echo -e "\nBuilding libtmpl Shared Object (.so file)"
sharedobjectlist=""
for filename in ./*.o; do
    sharedobjectlist="$sharedobjectlist $filename"
done

$CC $sharedobjectlist -O3 -flto -shared -o libtmpl.so -lm

echo "Moving to /usr/local/lib/libtmpl.so"
sudo mv libtmpl.so /usr/local/lib/libtmpl.so

echo "Setting LD_LIBRARY_PATH environment variable to include /usr/local/lib..."
if [[ $LD_LIBRARY_PATH != *"/usr/local/lib"* ]]; then
    echo -e "\n# Needed for loading libtmpl." >> ~/.bashrc
    echo "LD_LIBRARY_PATH=/usr/local/lib" >> ~/.bashrc
    echo "export LD_LIBRARY_PATH" >> ~/.bashrc
    source ~/.bashrc
fi

echo "Cleaning up..."
rm -f *.o

echo "Done"