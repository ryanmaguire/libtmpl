#!/bin/bash

# This file is for building libtmpl "in-place", meaning the compiled .so will
# remain in this directory and the include files (header files with .h) will
# remain here as well. This should only be used if you are building on a
# system where you DO NOT have root/sudo privileges.

#   Choose whatever C compiler you want. Tested with gcc, clang, tcc, and pcc
#   on GNU/Linux (Debian, Ubuntu, Fedora, and more) and FreeBSD 12.1.
CC=gcc

# Linking arguments.
# -O3 is optimization level 3.
# -I../ means include the parent directory so libtmpl/ is in the path.
# -flto is link time optimization.
# -lm means link against the standard math library.
# -o means create an output.
# -shared means the output is a shared object, like a library file.
SONAME="libtmpl.so"
LinkerArgs="-O3 -I../ -flto -shared -o $SONAME -lm"

# Name of the header file containing endianness info. We need to create this.
END_HEADER=include/tmpl_endianness.h

# C file for determining endianness and creating END_HEADER.
DET_END_FILE=./det_end.c

# Name of the executable create by DET_END_FILE.
DET_END_EXEC=det_end_out

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
elif [ $CC == "pcc" ]; then
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
if [ -e "$END_HEADER" ]; then
    rm -f "$END_HEADER";
fi

echo "Creating include/tmpl_endianness.h file..."
$CC $DET_END_FILE -o $DET_END_EXEC
./$DET_END_EXEC
rm -f $DET_END_EXEC

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

$CC $sharedobjectlist $LinkerArgs

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

echo -e "Done\n"

echo "PLEASE NOTE:"
echo -e "\tYou used the in-place script."
echo -e "\tlibtmpl was only installed in this directory:"
echo -e "\t\t$(pwd)."
echo -e "\tTo use libtmpl you must have this in your path."
echo -e "\tThe header files are located in:"
echo -e "\t\t$(pwd)/include/"
echo -e "\tand have NOT been placed in /usr/local/include/"
echo -e "\tYour compiler will not see these if you"
echo -e "\tdo not pass the correct options."
echo -e "\tFor most compilers (GCC, Clang, PCC, TCC) you can link"
echo -e "\tlibtmpl to you programs with the proper include"
echo -e "\tdirectories using the -I and -L option as follows:"
echo -e "\t\tgcc -I$(pwd)/../ -L$(pwd)/ my_file.c -o my_output -ltmpl"
