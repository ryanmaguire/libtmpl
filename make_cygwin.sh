
#   Choose whatever C compiler you want. Tested with gcc, clang, tcc, and pcc
#   on GNU/Linux (Debian, Ubuntu, Fedora, and more) and FreeBSD 12.1.
CC=clang
STDVER="-std=c89"
USEOMP=0

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
        echo "Invalid argument"
        echo "$arg"
        exit 0
    fi
done

if [ $USEOMP == 1 ]; then
    STDVER="$STDVER -fopenmp"
fi

SONAME="libtmpl.dll"
SODIR="./"

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

# Name of the header file containing endianness info. We need to create this.
END_HEADER=include/tmpl_endianness.h

# C file for determining endianness and creating END_HEADER.
DET_END_FILE=./det_end.c

# Name of the executable create by DET_END_FILE.
DET_END_EXEC=det_end_out.exe

if [ $CC == "clang" ]; then
    CArgs1="$STDVER -pedantic -pedantic-errors -Wall -Wextra -Wpedantic"
    CArgs2="-Wmissing-field-initializers -Wconversion -Weverything"
    CArgs3="-Wmissing-prototypes -Wold-style-definition -Winit-self"
    CArgs4="-Wmissing-declarations -Wnull-dereference -Wwrite-strings"
    CArgs5="-Wdouble-promotion -Wfloat-conversion -Wstrict-prototypes"
    CArgs6="-DNDEBUG -g -fPIC -O3 -flto -c"
    CompilerArgs="$CArgs1 $CArgs2 $CArgs3 $CArgs4 $CArgs5 $CArgs6"
else
    CArgs1="$STDVER -pedantic -Wall -Wextra -Wpedantic"
    CArgs2="-Wmisleading-indentation -Wmissing-field-initializers -Wconversion"
    CArgs3="-Wmissing-prototypes -Wold-style-definition -Winit-self"
    CArgs4="-Wmissing-declarations -Wnull-dereference -Wwrite-strings"
    CArgs5="-Wdouble-promotion -Wfloat-conversion -Wstrict-prototypes"
    CArgs6="-DNDEBUG -g -fPIC -O3 -flto -c"
    CompilerArgs="$CArgs1 $CArgs2 $CArgs3 $CArgs4 $CArgs5 $CArgs6"
fi

echo -e "\nClearing older files..."

#   There may be left-over .so and .o files from a previous build. Remove those
#   to avoid a faulty build.
rm -f *.so *.o *.dll
if [ -e "$END_HEADER" ]; then
    rm -f "$END_HEADER";
fi

echo "Creating include/tmpl_endianness.h file..."
$CC $DET_END_FILE -o $DET_END_EXEC
./$DET_END_EXEC
rm -f $DET_END_EXEC

echo "Compiling libtmpl..."
echo -e "\n\tCompiler Options:"
echo -e "\t\tCompiler: $CC"
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

echo -e "\nBuilding libtmp.dll file"

$CC ./*.o $LinkerArgs

echo "Cleaning up..."
rm -f *.o

echo "Done"
