#!/bin/bash

CC=gcc

echo -e "\nClearing older files..."
rm -f *.so
rm -f *.o

echo "Compiling libtmpl_compare..."
CompilerArgs1="-std=c99 -pedantic -pedantic-errors -Wall -Wextra -Wdouble-promotion"
CompilerArgs2="-Wpedantic -Wmisleading-indentation -Wmissing-field-initializers"
CompilerArgs3="-Wmissing-prototypes -Wold-style-definition -Winit-self"
CompilerArgs4="-Wmissing-declarations -Wstrict-prototypes -I./ -O3 -c"
CompilerArgs="$CompilerArgs1 $CompilerArgs2 $CompilerArgs3 $CompilerArgs4"

echo -e "\n\tCompiler Options:"
echo -e "\t\t$CompilerArgs1"
echo -e "\t\t$CompilerArgs2"
echo -e "\t\t$CompilerArgs3"
echo -e "\t\t$CompilerArgs4"

echo -e "\n\tCompiling Test Functions:"
$CC $CompilerArgs tmpl_float_1in1out.c

echo -e "\nBuilding Shared Object (.so file)"

sharedobjectlist=""
for filename in ./*.o; do
    sharedobjectlist="$sharedobjectlist $filename"
done

$CC $sharedobjectlist -shared -o libtmpl_compare.so -ltmpl -lm

echo "Moving to /usr/local/lib/libtmpl_compare.so"
sudo mv libtmpl_compare.so /usr/local/lib/libtmpl_compare.so

echo "Copying header file to /usr/local/include/libtmpl/"
includedir="/usr/local/include/libtmpl/"

#   Check if /usr/local/include/libtmpl/ is already a directory. If not
#   then create this via mkdir.
[ ! -d "$includedir" ] && sudo mkdir -p "$includedir/include/"
sudo cp tmpl_compare_funcs.h "$includedir/include/"

echo "Cleaning up..."
rm -f *.o

echo "Done"
