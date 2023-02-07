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

# Version of C to be used. Change this with -std=cxx.
STDVER="-std=c89"

# Use of OpenMP, the multiprocessing API. Enable this with -omp.
USEOMP=0

# Build the file library in place and do no store any header or library files
# in /usr/local/include/ and /usr/local/lib/, respectively. Use this if you
# do not have sudo priviledges. Enable this with -inplace.
INPLACE=0

# Use inline code for small functions (like absolute value). Can give a speed
# boost, but makes that compiled library file a tiny bit bigger. Only works
# with compilers supporting C99 (or higher) or the GNU inline extension.
# Enable this with -inline.
USEINLINE=0

# Macro for long long support.
USELONGLONG=0

# Whether or not to use libtmpl's implementation of libm.
USEMATH=1

# Use of the IEEE-754 floating point format.
USEIEEE=1

# Whether or not to attempt to find fixed-width integers.
USEINT=1

# Whether or not to use memcpy when possible.
USEMEMCPY=0

# Compile the entire library by #include'ing all files into one translation
# unit. The compiler get's to the see the entire library at once and make many
# optimizations.
MAKEMONSTER=0

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

    # Check if the user wants to use a different version of the C language.
    elif [[ "$arg" == *"-std"* ]]; then
        STDVER=$arg

    # Check if OpenMP support is requested.
    elif [ "$arg" == "-omp" ]; then
        USEOMP=1

    # Check if the user wants to build libtmpl in the libtmpl/ directory.
    elif [ "$arg" == "-inplace" ]; then
        INPLACE=1

    # Check if the user wants to inline small functions.
    elif [ "$arg" == "-inline" ]; then
        USEINLINE=1

    elif [ "$arg" == "-nomath" ]; then
        USEMATH=0

    elif [ "$arg" == "-noieee" ]; then
        USEIEEE=0

    elif [ "$arg" == "-noint" ]; then
        USEINT=0

    elif [ "$arg" == "-monster" ]; then
        MAKEMONSTER=1

    elif [ "$arg" == "-longlong" ]; then
        USELONGLONG=1

    elif [ "$arg" == "-memcpy" ]; then
        USEMEMCPY=1

    elif [ "$arg" == "-remove" ]; then
        SONAME="libtmpl.so"
        SODIR="/usr/local/lib"
        INCLUDE_TARGET=/usr/local/include/libtmpl/
        CONFIG_HEADER=include/tmpl_config.h
        INTEGER_HEADER=include/tmpl_inttype.h
        LIMITS_HEADER=include/tmpl_limits.h

        echo "Removing libtmpl:"
        echo "    Clearing older files..."
        rm -f *.so *.o *.obj *.lib

        echo "    Removing config header file if it exists..."
        if [ -e "$CONFIG_HEADER" ]; then
            rm -f "$CONFIG_HEADER";
        fi

        echo "    Removing integer header file if it exists..."
        if [ -e "$INTEGER_HEADER" ]; then
            rm -f "$INTEGER_HEADER";
        fi

        echo "    Removing limits header file if it exists..."
        if [ -e "$LIMITS_HEADER" ]; then
            rm -f "$LIMITS_HEADER";
        fi

        echo -e "    Removing include directory if it exists..."
        if [ -d "$INCLUDE_TARGET" ]; then
            rm -rf "$INCLUDE_TARGET";
        fi

        echo "    Removing shared object file if it exists..."
        if [ -e "$SODIR/$SONAME" ]; then
            rm -f "$SODIR/$SONAME";
        fi

        echo "libtmpl removed."
        exit 1

    # Check for any extra arguments.
    else
        ExtraArgs="$ExtraArgs ${arg#*}"
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

# If we're inlining small functions, we must not also compile the files
# containing these functions. The inline functions are defined in their
# respective header files. Create an exclude list with all functions that
# should not be compiled. The file det_inline.c creates a macro for libtmpl as
# to whether or not inline support has been requested. Define the macro
# TMPL_SET_INLINE_TRUE with -DTMPL_SET_INLINE_TRUE to enable this macro.
if [ $USEINLINE == 1 ]; then
    ExtraArgs="$ExtraArgs -DTMPL_SET_INLINE_TRUE"
    Exclude="$Exclude tmpl_abs_char.c"
    Exclude="$Exclude tmpl_abs_int.c"
    Exclude="$Exclude tmpl_abs_short.c"
    Exclude="$Exclude tmpl_abs_long.c"
    Exclude="$Exclude tmpl_abs_llong.c"
    Exclude="$Exclude tmpl_abs_double.c"
    Exclude="$Exclude tmpl_abs_float.c"
    Exclude="$Exclude tmpl_abs_ldouble.c"
    Exclude="$Exclude tmpl_arccos_pade_double.c"
    Exclude="$Exclude tmpl_arccos_pade_float.c"
    Exclude="$Exclude tmpl_arccos_pade_ldouble.c"
    Exclude="$Exclude tmpl_arccos_tail_end_double.c"
    Exclude="$Exclude tmpl_arccos_tail_end_float.c"
    Exclude="$Exclude tmpl_arccos_tail_end_ldouble.c"
    Exclude="$Exclude tmpl_arctan_asymptotic_double.c"
    Exclude="$Exclude tmpl_arctan_asymptotic_float.c"
    Exclude="$Exclude tmpl_arctan_asymptotic_ldouble.c"
    Exclude="$Exclude tmpl_arctan_maclaurin_double.c"
    Exclude="$Exclude tmpl_arctan_maclaurin_float.c"
    Exclude="$Exclude tmpl_arctan_maclaurin_ldouble.c"
    Exclude="$Exclude tmpl_arctan_pade_double.c"
    Exclude="$Exclude tmpl_arctan_pade_float.c"
    Exclude="$Exclude tmpl_arctan_pade_ldouble.c"
    Exclude="$Exclude tmpl_bessel_i0_asymptotic_double.c"
    Exclude="$Exclude tmpl_bessel_i0_asymptotic_float.c"
    Exclude="$Exclude tmpl_bessel_i0_chebyshev_double.c"
    Exclude="$Exclude tmpl_bessel_i0_chebyshev_float.c"
    Exclude="$Exclude tmpl_bessel_i0_maclaurin_double.c"
    Exclude="$Exclude tmpl_bessel_i0_maclaurin_float.c"
    Exclude="$Exclude tmpl_cbrt_pade_double.c"
    Exclude="$Exclude tmpl_cbrt_pade_float.c"
    Exclude="$Exclude tmpl_cbrt_pade_ldouble.c"
    Exclude="$Exclude tmpl_cbrt_taylor_double.c"
    Exclude="$Exclude tmpl_cbrt_taylor_float.c"
    Exclude="$Exclude tmpl_cbrt_taylor_ldouble.c"
    Exclude="$Exclude tmpl_arctan_very_small_double.c"
    Exclude="$Exclude tmpl_arctan_very_small_float.c"
    Exclude="$Exclude tmpl_arctan_very_small_ldouble.c"
    Exclude="$Exclude tmpl_complex_abs_double.c"
    Exclude="$Exclude tmpl_complex_abs_float.c"
    Exclude="$Exclude tmpl_complex_abs_ldouble.c"
    Exclude="$Exclude tmpl_complex_abs_squared_double.c"
    Exclude="$Exclude tmpl_complex_abs_squared_float.c"
    Exclude="$Exclude tmpl_complex_abs_squared_ldouble.c"
    Exclude="$Exclude tmpl_complex_add_double.c"
    Exclude="$Exclude tmpl_complex_add_float.c"
    Exclude="$Exclude tmpl_complex_add_ldouble.c"
    Exclude="$Exclude tmpl_complex_add_imag_double.c"
    Exclude="$Exclude tmpl_complex_add_imag_float.c"
    Exclude="$Exclude tmpl_complex_add_imag_ldouble.c"
    Exclude="$Exclude tmpl_complex_add_real_double.c"
    Exclude="$Exclude tmpl_complex_add_real_float.c"
    Exclude="$Exclude tmpl_complex_add_real_ldouble.c"
    Exclude="$Exclude tmpl_complex_addto_double.c"
    Exclude="$Exclude tmpl_complex_addto_float.c"
    Exclude="$Exclude tmpl_complex_addto_ldouble.c"
    Exclude="$Exclude tmpl_complex_addto_imag_double.c"
    Exclude="$Exclude tmpl_complex_addto_imag_float.c"
    Exclude="$Exclude tmpl_complex_addto_imag_ldouble.c"
    Exclude="$Exclude tmpl_complex_addto_real_double.c"
    Exclude="$Exclude tmpl_complex_addto_real_float.c"
    Exclude="$Exclude tmpl_complex_addto_real_ldouble.c"
    Exclude="$Exclude tmpl_complex_argument_double.c"
    Exclude="$Exclude tmpl_complex_argument_float.c"
    Exclude="$Exclude tmpl_complex_argument_ldouble.c"
    Exclude="$Exclude tmpl_complex_conjugate_double.c"
    Exclude="$Exclude tmpl_complex_conjugate_float.c"
    Exclude="$Exclude tmpl_complex_conjugate_ldouble.c"
    Exclude="$Exclude tmpl_complex_conjugateself_double.c"
    Exclude="$Exclude tmpl_complex_conjugateself_float.c"
    Exclude="$Exclude tmpl_complex_conjugateself_ldouble.c"
    Exclude="$Exclude tmpl_complex_dist_double.c"
    Exclude="$Exclude tmpl_complex_dist_float.c"
    Exclude="$Exclude tmpl_complex_dist_ldouble.c"
    Exclude="$Exclude tmpl_complex_dist_squared_double.c"
    Exclude="$Exclude tmpl_complex_dist_squared_float.c"
    Exclude="$Exclude tmpl_complex_dist_squared_ldouble.c"
    Exclude="$Exclude tmpl_complex_multiply_double.c"
    Exclude="$Exclude tmpl_complex_multiply_float.c"
    Exclude="$Exclude tmpl_complex_multiply_ldouble.c"
    Exclude="$Exclude tmpl_complex_multiply_imag_double.c"
    Exclude="$Exclude tmpl_complex_multiply_imag_float.c"
    Exclude="$Exclude tmpl_complex_multiply_imag_ldouble.c"
    Exclude="$Exclude tmpl_complex_multiply_real_double.c"
    Exclude="$Exclude tmpl_complex_multiply_real_float.c"
    Exclude="$Exclude tmpl_complex_multiply_real_ldouble.c"
    Exclude="$Exclude tmpl_complex_quick_abs_double.c"
    Exclude="$Exclude tmpl_complex_quick_abs_float.c"
    Exclude="$Exclude tmpl_complex_quick_abs_ldouble.c"
    Exclude="$Exclude tmpl_complex_quick_dist_double.c"
    Exclude="$Exclude tmpl_complex_quick_dist_float.c"
    Exclude="$Exclude tmpl_complex_quick_dist_ldouble.c"
    Exclude="$Exclude tmpl_copysign_float.c"
    Exclude="$Exclude tmpl_copysign_double.c"
    Exclude="$Exclude tmpl_copysign_ldouble.c"
    Exclude="$Exclude tmpl_cosd_maclaurin_double.c"
    Exclude="$Exclude tmpl_cosd_maclaurin_float.c"
    Exclude="$Exclude tmpl_cosd_maclaurin_ldouble.c"
    Exclude="$Exclude tmpl_cosh_maclaurin_double.c"
    Exclude="$Exclude tmpl_cosh_maclaurin_float.c"
    Exclude="$Exclude tmpl_cosh_maclaurin_ldouble.c"
    Exclude="$Exclude tmpl_cosh_pade_double.c"
    Exclude="$Exclude tmpl_cosh_pade_float.c"
    Exclude="$Exclude tmpl_cosh_pade_ldouble.c"
    Exclude="$Exclude tmpl_cospi_maclaurin_double.c"
    Exclude="$Exclude tmpl_cospi_maclaurin_float.c"
    Exclude="$Exclude tmpl_cospi_maclaurin_ldouble.c"
    Exclude="$Exclude tmpl_dist_float.c"
    Exclude="$Exclude tmpl_dist_double.c"
    Exclude="$Exclude tmpl_dist_ldouble.c"
    Exclude="$Exclude tmpl_erf_asymptotic_double.c"
    Exclude="$Exclude tmpl_erf_chebyshev_double.c"
    Exclude="$Exclude tmpl_erf_maclaurin_double.c"
    Exclude="$Exclude tmpl_erf_pade_double.c"
    Exclude="$Exclude tmpl_exp_maclaurin_double.c"
    Exclude="$Exclude tmpl_exp_maclaurin_float.c"
    Exclude="$Exclude tmpl_exp_maclaurin_ldouble.c"
    Exclude="$Exclude tmpl_exp_pade_double.c"
    Exclude="$Exclude tmpl_exp_pade_float.c"
    Exclude="$Exclude tmpl_exp_pade_ldouble.c"
    Exclude="$Exclude tmpl_exp_pos_kernel_double.c"
    Exclude="$Exclude tmpl_exp_pos_kernel_float.c"
    Exclude="$Exclude tmpl_exp_pos_kernel_ldouble.c"
    Exclude="$Exclude tmpl_exp_neg_kernel_double.c"
    Exclude="$Exclude tmpl_exp_neg_kernel_float.c"
    Exclude="$Exclude tmpl_exp_neg_kernel_ldouble.c"
    Exclude="$Exclude tmpl_exp_remez_double.c"
    Exclude="$Exclude tmpl_exp_remez_float.c"
    Exclude="$Exclude tmpl_exp_remez_ldouble.c"
    Exclude="$Exclude tmpl_sin_pade_double.c"
    Exclude="$Exclude tmpl_sin_pade_float.c"
    Exclude="$Exclude tmpl_sin_pade_ldouble.c"
    Exclude="$Exclude tmpl_sin_pade_pi_double.c"
    Exclude="$Exclude tmpl_sin_pade_pi_float.c"
    Exclude="$Exclude tmpl_sin_pade_pi_ldouble.c"
    Exclude="$Exclude tmpl_sin_very_small_double.c"
    Exclude="$Exclude tmpl_sind_maclaurin_double.c"
    Exclude="$Exclude tmpl_sind_maclaurin_float.c"
    Exclude="$Exclude tmpl_sind_maclaurin_ldouble.c"
    Exclude="$Exclude tmpl_sinpi_maclaurin_double.c"
    Exclude="$Exclude tmpl_sinpi_maclaurin_float.c"
    Exclude="$Exclude tmpl_sinpi_maclaurin_ldouble.c"
    Exclude="$Exclude tmpl_two_vector_l2_norm_double.c"
    Exclude="$Exclude tmpl_two_vector_l2_norm_float.c"
    Exclude="$Exclude tmpl_two_vector_l2_norm_ldouble.c"
fi

if [ $USELONGLONG == 0 ]; then
    ExtraArgs="$ExtraArgs -DTMPL_SET_LONGLONG_FALSE"
    Exclude="$Exclude tmpl_abs_llong.c"
    Exclude="$Exclude tmpl_factorial_ullong.c"
    Exclude="$Exclude tmpl_leading_zeros_ullong.c"
fi

if [ $USEMATH == 1 ]; then
    ExtraArgs="$ExtraArgs -DTMPL_SET_USE_MATH_TRUE"
else
    Exclude="$Exclude tmpl_abs_double.c"
    Exclude="$Exclude tmpl_abs_float.c"
    Exclude="$Exclude tmpl_abs_ldouble.c"
    Exclude="$Exclude tmpl_arctan_tables.c"
    Exclude="$Exclude tmpl_arctan2_double.c"
    Exclude="$Exclude tmpl_arctan2_float.c"
    Exclude="$Exclude tmpl_arctan2_ldouble.c"
    Exclude="$Exclude tmpl_arctan_double.c"
    Exclude="$Exclude tmpl_arctan_float.c"
    Exclude="$Exclude tmpl_arctan_ldouble.c"
    Exclude="$Exclude tmpl_cos_double.c"
    Exclude="$Exclude tmpl_floor_double.c"
    Exclude="$Exclude tmpl_floor_float.c"
    Exclude="$Exclude tmpl_sin_double.c"
fi

if [ $USEIEEE == 0 ]; then
    ExtraArgs="$ExtraArgs -DTMPL_SET_TMPL_USE_IEEE_FALSE"
fi

if [ $USEINT == 0 ]; then
    ExtraArgs="$ExtraArgs -DTMPL_SET_NO_INT"
fi

if [ $USEMEMCPY == 1 ]; then
    ExtraArgs="$ExtraArgs -DTMPL_SET_USE_MEMCPY_TRUE"
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
    LinkerArgs="-O3 -flto -fopenmp -shared -o $SONAME -lm"
else
    LinkerArgs="-O3 -flto -shared -o $SONAME -lm"
fi

# Location where the .h files will be stored.
INCLUDE_TARGET=/usr/local/include/libtmpl/

# Header file that needs to be created prior to building libtmpl.
CONFIG_HEADER=include/tmpl_config.h

# C file for creating this header.
CONFIG_FILE=config.c

# Name of the executable to create this header.
CONFIG_EXEC=config.out

# There may be left-over .so and .o files from a previous build. Remove those
# to avoid a faulty build.
echo "Clearing older files"
rm -f *.so *.o *.obj *.lib

# If the config header already exists, remove it.
if [ -e "$CONFIG_HEADER" ]; then
    rm -f "$CONFIG_HEADER";
fi

# If we're not building libtmpl into libtmpl/, clear older files.
if [ $INPLACE == 0 ]; then

    # Clear older header files.
    if [ -d "$INCLUDE_TARGET" ]; then
        echo "Clearing $INCLUDE_TARGET"
        rm -rf "$INCLUDE_TARGET";
    fi

    # Clear older library files.
    if [ -e "$SODIR/$SONAME" ]; then
        echo "Erasing $SODIR/$SONAME"
        rm -f "$SODIR/$SONAME";
    fi
fi

# Create the config header.
echo "Creating $CONFIG_HEADER"
$CC $STDVER $ExtraArgs $CONFIG_FILE -o $CONFIG_EXEC
./$CONFIG_EXEC
rm -f $CONFIG_EXEC

echo ""
echo "Compiling libtmpl"
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

if [ $MAKEMONSTER == 1 ]; then

    if [ -e "monster.c" ]; then
        rm -f monster.c;
    fi

    touch monster.c

    for file in include/*.h; do
        echo "#include \"$file\"" >> monster.c;
    done

    for dir in src/*/; do

        # assembly and buitlins only has assembly code. Skip this.
        if [[ $dir == *"assembly"* ]]; then
            continue;
        fi

        for filename in $dir*.c; do
            filename_without_path=$(basename -- $filename)
            if [[ $Exclude == *"$filename_without_path"* ]]; then
                continue;
            fi
            echo "#include \"$filename\"" >> monster.c;
        done
    done

    echo "Compiling libtmpl..."
    if !($CC $CompilerArgs monster.c); then
        exit 1
    fi

    echo "Building libtmpl Shared Object (.so file)"
    if !($CC ./*.o $LinkerArgs); then
        exit 1
    fi

    rm -f *.o
    rm -f monster.c
else

    # Loop over all directories in src/ and compile all .c files.
    for dir in src/*; do

        # assembly and buitlins only has assembly code. Skip this.
        if [[ $dir == *"assembly"* ]]; then
            continue;
        fi

        echo ""
        echo "    Compiling $dir"
        for filename in $dir/*.c; do
            filename_without_path=$(basename -- $filename)
            if [[ $Exclude == *"$filename_without_path"* ]]; then
                continue;
            fi

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
fi

# If inplace is set, we can't use sudo.
if [ $INPLACE == 0 ]; then

    # Copy the header files to the appropriate directory.
    echo "Copying include/ directory to $INCLUDE_TARGET"
    mkdir -p "$INCLUDE_TARGET"
    cp -r ./include/ "$INCLUDE_TARGET"

    # Move the shared object file to the appropriate directory.
    echo "Moving $SONAME to $SODIR"
    mv $SONAME $SODIR
fi

echo "Cleaning up"
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

