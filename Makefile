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
#   Date:       August 31, 2021                                                #
################################################################################

# This Makefile currently uses GNU Make features. Use gmake on BSD systems and
# make on macOS and GNU/Linux.

#   OPTIONS:
#       CC:
#           C compiler to be used. Tested with:
#               gcc:   GNU C compiler.
#               clang: LLVM's C compiler.
#               tcc:   The Tiny C Compiler
#               pcc:   The Portable C Compiler
#               aocc:  AMD's optimizing C Compiler
#       OMP:
#           Set OpenMP flags. Useful if you want to build libtmpyl, the Python
#           wrapper for libtmpl, and use with numpy arrays for parallel
#           computing. Enable with:
#               make OMP=1 [other-options]
#       NO_MATH:
#           Do not use libtmpl's implementation of libm, the C standard
#           mathematical library. You must have C99 or higher support if you
#           wish to enable this. The original C89 standard does not require
#           float and long double versions of various functions, whereas
#           libtmpl makes use of these.
#               make NO_MATH=1 [other-options]
#       NO_LONGLONG:
#           libtmpl provides many functions for integer data types. The config.c
#           file will examine the __STDC_VERSION__ macro to check if long long
#           is available. If you do not wish to build long long functions at
#           all, set this option (for example, you're on a GNU/Linux machine
#           where the long and long long data types are the same). Enable with:
#               make NO_LONGLONG=1 [other-options]
#       NO_INLINE:
#           libtmpl allows many smaller functions to be inlined, resulting in
#           significant speed boosts in several cases (tmpl_Double_Abs is about
#           2x faster when inlined, for example). The config.c file will check
#           the __STDC_VERSION__ macro to see if inline support is available.
#           If you do not wish to use inlined code, set this option. Enable via:
#               make NO_INLINE=1 [other-options]
#       NO_IEEE:
#           Many functions use type punning to take advantage of the IEEE-754
#           format for floating point numbers. Type punning is technically
#           undefined behavior, but every compiler I know supports it. The
#           config.c file will check if you have IEEE-754 support with type
#           punning. If you wish to force the portable code to be used, set this
#           option. Note, the portable algorithms are significantly slower.
#               make NO_IEEE=1 [other-options]
#       NO_INT:
#           In a few cases it useful to have fixed-width (8, 16, 32, and 64) bit
#           integers. The C standard does not require these widths be available
#           but rather specifies the minimum widths allowed by certain data
#           types. The config.c file will try to find the widths of various
#           integer types. To skip this, set this option. Enable with:
#               make NO_INT=1 [other-options]

# Name of the library.
TARGET_LIB=libtmpl.so

# Directory all of the .o files will be placed in.
BUILD_DIR=./build

# Location of all .c and .S files.
SRC_DIRS=./src

# Compiler to be used. Override this to whatever you choose.
CC=cc

# Some functions use omp with for-loops (void_pointer functions), if available.
ifdef OMP
OMP_FLAGS=-fopenmp
else
OMP_FLAGS=
endif

# Some old functions still call math.h. This will be replaced soon.
ifdef NO_MATH
MATH_FLAGS=-lm
else
MATH_FLAGS=-lm
endif

CFLAGS=$(OMP_FLAGS) -I../ -O3 -fPIC -flto -DNDEBUG -c
LFLAGS=$(OMP_FLAGS) -O3 -flto -shared $(MATH_FLAGS) $(EXTRA_LFLAGS)
CWARN=-Wall -Wextra -Wpedantic $(EXTRA_FLAGS)

# libtmpl will check if long long is available in config.c. If you do not want
# long long functions compiled (for example, you're on a GNU/Linux machine where
# long and long long are the same thing), set this option.
ifdef NO_LONGLONG
LL_FLAG=-DTMPL_SET_LONGLONG_FALSE
LL_EXCLUDE=\
	-not -name "tmpl_abs_llong.c" -and
else
LL_FLAG=
LL_EXCLUDE=
endif

# libtmpl provides its own implementation of libm. If you wish to use the
# default libm implementation (if it exists) for your system enable this option.
ifdef NO_MATH
MATH_FLAG=
MATH_EXCLUDE=\
	-not -name "tmpl_abs_double.c" -and \
	-not -name "tmpl_abs_float.c" -and \
	-not -name "tmpl_abs_ldouble.c" -and \
	-not -name "tmpl_arccos_double.c" -and \
	-not -name "tmpl_arccos_float.c" -and \
	-not -name "tmpl_arccos_ldouble.c" -and \
	-not -name "tmpl_arcsin_double.c" -and \
	-not -name "tmpl_arcsin_float.c" -and \
	-not -name "tmpl_arcsin_ldouble.c" -and \
	-not -name "tmpl_arctan2_double.c" -and \
	-not -name "tmpl_arctan2_float.c" -and \
	-not -name "tmpl_arctan2_ldouble.c" -and \
	-not -name "tmpl_arctan_double.c" -and \
	-not -name "tmpl_arctan_float.c" -and \
	-not -name "tmpl_arctan_ldouble.c" -and \
	-not -name "tmpl_cos_double.c" -and \
	-not -name "tmpl_floor_double.c" -and \
	-not -name "tmpl_floor_float.c" -and \
	-not -name "tmpl_sin_double.c" -and
else
MATH_FLAG=-DTMPL_SET_USE_MATH_TRUE
MATH_EXCLUDE=
endif

# libtmpl will check if inline support is available in config.c. If you do not
# want to inline functions, set this option.
ifdef NO_INLINE
INLINE_FLAG=
INLINE_EXCLUDE=
else
INLINE_FLAG=-DTMPL_SET_INLINE_TRUE
INLINE_EXCLUDE=\
	-not -name "tmpl_abs_char.c" -and \
	-not -name "tmpl_abs_short.c" -and \
	-not -name "tmpl_abs_int.c" -and \
	-not -name "tmpl_abs_long.c" -and \
	-not -name "tmpl_abs_llong.c" -and \
	-not -name "tmpl_abs_double.c" -and \
	-not -name "tmpl_abs_float.c" -and \
	-not -name "tmpl_abs_ldouble.c" -and \
	-not -name "tmpl_arccos_maclaurin_double.c" -and \
	-not -name "tmpl_arccos_maclaurin_float.c" -and \
	-not -name "tmpl_arccos_maclaurin_ldouble.c" -and \
	-not -name "tmpl_arccos_pade_double.c" -and \
	-not -name "tmpl_arccos_pade_float.c" -and \
	-not -name "tmpl_arccos_pade_ldouble.c" -and \
	-not -name "tmpl_arccos_rat_remez_double.c" -and \
	-not -name "tmpl_arccos_rat_remez_float.c" -and \
	-not -name "tmpl_arccos_rat_remez_ldouble.c" -and \
	-not -name "tmpl_arccos_tail_end_double.c" -and \
	-not -name "tmpl_arccos_tail_end_float.c" -and \
	-not -name "tmpl_arccos_tail_end_ldouble.c" -and \
	-not -name "tmpl_arcsin_maclaurin_double.c" -and \
	-not -name "tmpl_arcsin_maclaurin_float.c" -and \
	-not -name "tmpl_arcsin_maclaurin_ldouble.c" -and \
	-not -name "tmpl_arcsin_pade_double.c" -and \
	-not -name "tmpl_arcsin_pade_float.c" -and \
	-not -name "tmpl_arcsin_pade_ldouble.c" -and \
	-not -name "tmpl_arcsin_rat_remez_double.c" -and \
	-not -name "tmpl_arcsin_rat_remez_float.c" -and \
	-not -name "tmpl_arcsin_rat_remez_ldouble.c" -and \
	-not -name "tmpl_arcsin_tail_end_double.c" -and \
	-not -name "tmpl_arcsin_tail_end_float.c" -and \
	-not -name "tmpl_arcsin_tail_end_ldouble.c" -and \
	-not -name "tmpl_arctan_asymptotic_double.c" -and \
	-not -name "tmpl_arctan_asymptotic_float.c" -and \
	-not -name "tmpl_arctan_asymptotic_ldouble.c" -and \
	-not -name "tmpl_arctan_maclaurin_double.c" -and \
	-not -name "tmpl_arctan_maclaurin_float.c" -and \
	-not -name "tmpl_arctan_maclaurin_ldouble.c" -and \
	-not -name "tmpl_arctan_pade_double.c" -and \
	-not -name "tmpl_arctan_pade_float.c" -and \
	-not -name "tmpl_arctan_pade_ldouble.c" -and \
	-not -name "tmpl_arctan_very_small_double.c" -and \
	-not -name "tmpl_arctan_very_small_float.c" -and \
	-not -name "tmpl_arctan_very_small_ldouble.c" -and \
	-not -name "tmpl_bessel_i0_asymptotic_double.c" -and \
	-not -name "tmpl_bessel_i0_asymptotic_float.c" -and \
	-not -name "tmpl_bessel_i0_chebyshev_double.c" -and \
	-not -name "tmpl_bessel_i0_chebyshev_float.c" -and \
	-not -name "tmpl_bessel_i0_maclaurin_double.c" -and \
	-not -name "tmpl_bessel_i0_maclaurin_float.c" -and \
	-not -name "tmpl_cbrt_pade_double.c" -and \
	-not -name "tmpl_cbrt_pade_float.c" -and \
	-not -name "tmpl_cbrt_pade_ldouble.c" -and \
	-not -name "tmpl_cbrt_taylor_double.c" -and \
	-not -name "tmpl_cbrt_taylor_float.c" -and \
	-not -name "tmpl_cbrt_taylor_ldouble.c" -and \
	-not -name "tmpl_complex_abs_double.c" -and \
	-not -name "tmpl_complex_abs_float.c" -and \
	-not -name "tmpl_complex_abs_ldouble.c" -and \
	-not -name "tmpl_complex_abs_squared_double.c" -and \
	-not -name "tmpl_complex_abs_squared_float.c" -and \
	-not -name "tmpl_complex_abs_squared_ldouble.c" -and \
	-not -name "tmpl_complex_add_double.c" -and \
	-not -name "tmpl_complex_add_float.c" -and \
	-not -name "tmpl_complex_add_ldouble.c" -and \
	-not -name "tmpl_complex_add_imag_double.c" -and \
	-not -name "tmpl_complex_add_imag_float.c" -and \
	-not -name "tmpl_complex_add_imag_ldouble.c" -and \
	-not -name "tmpl_complex_add_real_double.c" -and \
	-not -name "tmpl_complex_add_real_float.c" -and \
	-not -name "tmpl_complex_add_real_ldouble.c" -and \
	-not -name "tmpl_complex_addto_double.c" -and \
	-not -name "tmpl_complex_addto_float.c" -and \
	-not -name "tmpl_complex_addto_ldouble.c" -and \
	-not -name "tmpl_complex_addto_imag_double.c" -and \
	-not -name "tmpl_complex_addto_imag_float.c" -and \
	-not -name "tmpl_complex_addto_imag_ldouble.c" -and \
	-not -name "tmpl_complex_addto_real_double.c" -and \
	-not -name "tmpl_complex_addto_real_float.c" -and \
	-not -name "tmpl_complex_addto_real_ldouble.c" -and \
	-not -name "tmpl_complex_argument_double.c" -and \
	-not -name "tmpl_complex_argument_float.c" -and \
	-not -name "tmpl_complex_argument_ldouble.c" -and \
	-not -name "tmpl_complex_conjugate_double.c" -and \
	-not -name "tmpl_complex_conjugate_float.c" -and \
	-not -name "tmpl_complex_conjugate_ldouble.c" -and \
	-not -name "tmpl_complex_conjugateself_double.c" -and \
	-not -name "tmpl_complex_conjugateself_float.c" -and \
	-not -name "tmpl_complex_conjugateself_ldouble.c" -and \
	-not -name "tmpl_complex_dist_double.c" -and \
	-not -name "tmpl_complex_dist_float.c" -and \
	-not -name "tmpl_complex_dist_ldouble.c" -and \
	-not -name "tmpl_complex_dist_squared_double.c" -and \
	-not -name "tmpl_complex_dist_squared_float.c" -and \
	-not -name "tmpl_complex_dist_squared_ldouble.c" -and \
	-not -name "tmpl_complex_expi_double.c" -and \
	-not -name "tmpl_complex_expi_float.c" -and \
	-not -name "tmpl_complex_expi_ldouble.c" -and \
	-not -name "tmpl_complex_expipi_double.c" -and \
	-not -name "tmpl_complex_expipi_float.c" -and \
	-not -name "tmpl_complex_expipi_ldouble.c" -and \
	-not -name "tmpl_complex_multiply_double.c" -and \
	-not -name "tmpl_complex_multiply_float.c" -and \
	-not -name "tmpl_complex_multiply_ldouble.c" -and \
	-not -name "tmpl_complex_multiply_imag_double.c" -and \
	-not -name "tmpl_complex_multiply_imag_float.c" -and \
	-not -name "tmpl_complex_multiply_imag_ldouble.c" -and \
	-not -name "tmpl_complex_multiply_real_double.c" -and \
	-not -name "tmpl_complex_multiply_real_float.c" -and \
	-not -name "tmpl_complex_multiply_real_ldouble.c" -and \
	-not -name "tmpl_complex_polar_double.c" -and \
	-not -name "tmpl_complex_polar_float.c" -and \
	-not -name "tmpl_complex_polar_ldouble.c" -and \
	-not -name "tmpl_complex_quick_abs_double.c" -and \
	-not -name "tmpl_complex_quick_abs_float.c" -and \
	-not -name "tmpl_complex_quick_abs_ldouble.c" -and \
	-not -name "tmpl_complex_quick_dist_double.c" -and \
	-not -name "tmpl_complex_quick_dist_float.c" -and \
	-not -name "tmpl_complex_quick_dist_ldouble.c" -and \
	-not -name "tmpl_copysign_float.c" -and \
	-not -name "tmpl_copysign_double.c" -and \
	-not -name "tmpl_copysign_ldouble.c" -and \
	-not -name "tmpl_cosd_maclaurin_double.c" -and \
	-not -name "tmpl_cosd_maclaurin_float.c" -and \
	-not -name "tmpl_cosd_maclaurin_ldouble.c" -and \
	-not -name "tmpl_cosh_maclaurin_double.c" -and \
	-not -name "tmpl_cosh_maclaurin_float.c" -and \
	-not -name "tmpl_cosh_maclaurin_ldouble.c" -and \
	-not -name "tmpl_cosh_pade_double.c" -and \
	-not -name "tmpl_cosh_pade_float.c" -and \
	-not -name "tmpl_cosh_pade_ldouble.c" -and \
	-not -name "tmpl_exp_maclaurin_double.c" -and \
	-not -name "tmpl_exp_maclaurin_float.c" -and \
	-not -name "tmpl_exp_maclaurin_ldouble.c" -and \
	-not -name "tmpl_exp_pade_double.c" -and \
	-not -name "tmpl_exp_pade_float.c" -and \
	-not -name "tmpl_exp_pade_ldouble.c" -and \
	-not -name "tmpl_cospi_maclaurin_double.c" -and \
	-not -name "tmpl_cospi_maclaurin_float.c" -and \
	-not -name "tmpl_cospi_maclaurin_ldouble.c" -and \
	-not -name "tmpl_exp_remez_double.c" -and \
	-not -name "tmpl_exp_remez_float.c" -and \
	-not -name "tmpl_exp_remez_ldouble.c" -and \
	-not -name "tmpl_dist_float.c" -and \
	-not -name "tmpl_dist_double.c" -and \
	-not -name "tmpl_dist_ldouble.c" -and \
	-not -name "tmpl_erf_asymptotic_double.c" -and \
	-not -name "tmpl_erf_chebyshev_double.c" -and \
	-not -name "tmpl_erf_maclaurin_double.c" -and \
	-not -name "tmpl_erf_pade_double.c" -and \
	-not -name "tmpl_exp_neg_kernel_double.c" -and \
	-not -name "tmpl_exp_neg_kernel_float.c" -and \
	-not -name "tmpl_exp_neg_kernel_ldouble.c" -and \
	-not -name "tmpl_exp_pos_kernel_double.c" -and \
	-not -name "tmpl_exp_pos_kernel_float.c" -and \
	-not -name "tmpl_exp_pos_kernel_ldouble.c" -and \
	-not -name "tmpl_is_inf_float.c" -and \
	-not -name "tmpl_is_inf_double.c" -and \
	-not -name "tmpl_is_inf_ldouble.c" -and \
	-not -name "tmpl_is_nan_float.c" -and \
	-not -name "tmpl_is_nan_double.c" -and \
	-not -name "tmpl_is_nan_ldouble.c" -and \
	-not -name "tmpl_positive_difference_double.c" -and \
	-not -name "tmpl_positive_difference_float.c" -and \
	-not -name "tmpl_positive_difference_ldouble.c" -and \
	-not -name "tmpl_sin_pade_double.c" -and \
	-not -name "tmpl_sin_pade_float.c" -and \
	-not -name "tmpl_sin_pade_ldouble.c" -and \
	-not -name "tmpl_sin_pade_pi_double.c" -and \
	-not -name "tmpl_sin_pade_pi_float.c" -and \
	-not -name "tmpl_sin_pade_pi_ldouble.c" -and \
	-not -name "tmpl_sind_maclaurin_double.c" -and \
	-not -name "tmpl_sind_maclaurin_float.c" -and \
	-not -name "tmpl_sind_maclaurin_ldouble.c" -and \
	-not -name "tmpl_sinpi_maclaurin_double.c" -and \
	-not -name "tmpl_sinpi_maclaurin_float.c" -and \
	-not -name "tmpl_sinpi_maclaurin_ldouble.c" -and \
	-not -name "tmpl_sin_very_small_double.c" -and \
	-not -name "tmpl_two_vector_l2_norm_double.c" -and \
	-not -name "tmpl_two_vector_l2_norm_float.c" -and \
	-not -name "tmpl_two_vector_l2_norm_ldouble.c" -and
endif

# Whether or not to use the strictly portable code, of IEEE-754 compliant code.
ifdef NO_IEEE
IEEE_FLAG=-DTMPL_SET_TMPL_USE_IEEE_FALSE
else
IEEE_FLAG=
endif

ifdef USE_MEMCPY
MEMCPY_FLAG=-DTMPL_SET_USE_MEMCPY_TRUE
else
MEMCPY_FLAG=
endif

# Whether or not to try and find fixed-width integer data types.
ifdef NO_INT
INT_FLAG=-DTMPL_SET_NO_INT
else
INT_FLAG=
endif

# The architecture libtmpl is being built on.
ifndef ARCH
uname_m=$(shell uname -m)
else
uname_m=$(ARCH)
endif

# If the user does not want to use any assembly code (that is, C only) only
# include .c files. Ignore all .S or .fasm files. For x86_64/amd64, aarch64,
# and armv7l (armhf) this is only advised if your C compiler cannot compile
# assembly code. GCC, Clang, and PCC can. I'm unsure about TCC.
ifdef NO_ASM
ASM_INCLUDE=
ASM_EXCLUDE=

# Else for ifdef NO_ASM
# amd64/x86_64 have various functions built-in, such as sqrt. Use assembly code
# if possible for performance boosts.
else ifeq ($(uname_m),$(filter $(uname_m),x86_64 amd64))

# Some function for x86_64 are written in FASM, the Flat Assembler, and have
# much better times than the default C code.
ifdef FASM
ASM_INCLUDE=-wholename "./src/assembly/fasm/*.fasm" -or
ASM_EXCLUDE=\
	-not -name "tmpl_trailing_zeros_char.c" -and \
	-not -name "tmpl_trailing_zeros_int.c" -and \
	-not -name "tmpl_trailing_zeros_long.c" -and \
	-not -name "tmpl_trailing_zeros_short.c" -and \
	-not -name "tmpl_trailing_zeros_uint.c" -and \
	-not -name "tmpl_trailing_zeros_uchar.c" -and \
	-not -name "tmpl_trailing_zeros_ulong.c" -and \
	-not -name "tmpl_trailing_zeros_ushort.c" -and \
	-not -name "tmpl_sqrt_double.c" -and \
	-not -name "tmpl_sqrt_float.c" -and \
	-not -name "tmpl_sqrt_ldouble.c" -and \
	-not -name "tmpl_floor_double.c" -and \
	-not -name "tmpl_floor_float.c" -and \
	-not -name "tmpl_floor_ldouble.c" -and

# The default is to use assembly code that GCC can understand. LLVM's clang and
# the Portable C Compiler (PCC) are also able to compile this, tested on
# Debian GNU/Linux 11.
else

ASM_INCLUDE=-wholename "./src/assembly/x86_64/*.S" -or
ASM_EXCLUDE=\
	-not -name "tmpl_trailing_zeros_char.c" -and \
	-not -name "tmpl_trailing_zeros_int.c" -and \
	-not -name "tmpl_trailing_zeros_long.c" -and \
	-not -name "tmpl_trailing_zeros_short.c" -and \
	-not -name "tmpl_trailing_zeros_uint.c" -and \
	-not -name "tmpl_trailing_zeros_uchar.c" -and \
	-not -name "tmpl_trailing_zeros_ulong.c" -and \
	-not -name "tmpl_trailing_zeros_ushort.c" -and \
	-not -name "tmpl_sqrt_double.c" -and \
	-not -name "tmpl_sqrt_float.c" -and \
	-not -name "tmpl_sqrt_ldouble.c" -and \
	-not -name "tmpl_floor_double.c" -and \
	-not -name "tmpl_floor_float.c" -and \
	-not -name "tmpl_floor_ldouble.c" -and
endif
# End of ifdef FASM.

else ifeq ($(uname_m),$(filter $(uname_m),i386 x86))

ASM_INCLUDE=-wholename "./src/assembly/i386/*.S" -or
ASM_EXCLUDE=\
	-not -name "tmpl_trailing_zeros_char.c" -and \
	-not -name "tmpl_trailing_zeros_int.c" -and \
	-not -name "tmpl_trailing_zeros_long.c" -and \
	-not -name "tmpl_trailing_zeros_short.c" -and \
	-not -name "tmpl_trailing_zeros_uint.c" -and \
	-not -name "tmpl_trailing_zeros_uchar.c" -and \
	-not -name "tmpl_trailing_zeros_ulong.c" -and \
	-not -name "tmpl_trailing_zeros_ushort.c" -and \
	-not -name "tmpl_sqrt_double.c" -and \
	-not -name "tmpl_sqrt_float.c" -and \
	-not -name "tmpl_sqrt_ldouble.c" -and \
	-not -name "tmpl_floor_double.c" -and \
	-not -name "tmpl_floor_float.c" -and \
	-not -name "tmpl_floor_ldouble.c" -and

# Else for ifdef NO_ASM
# Same idea, but for aarch64 (arm64). sqrt is also a built-in function.
else ifeq ($(uname_m),$(filter $(uname_m),aarch64 arm64))

ASM_INCLUDE=-wholename "./src/assembly/aarch64/*.S" -or
ASM_EXCLUDE=\
	-not -name "tmpl_floor_double.c" -and \
	-not -name "tmpl_floor_float.c" -and \
	-not -name "tmpl_sqrt_double.c" -and \
	-not -name "tmpl_sqrt_float.c" -and \

# Else for ifdef NO_ASM
# Same idea, but for armv7l (armhf). sqrt is also a built-in function.
else ifeq ($(uname_m),$(filter $(uname_m),armv7l))

ASM_INCLUDE=-wholename "./src/assembly/armv7l/*.S" -or
ASM_EXCLUDE=\
	-not -name "tmpl_sqrt_double.c" -and \
	-not -name "tmpl_sqrt_float.c" -and \
	-not -name "tmpl_sqrt_ldouble.c" -and

# Else for ifeq ($(uname_m),x86_64). Only amd64/x86_64 and aarch64/arm7l have
# assembly code support. This may change in the future. The rest of the C
# code has been tested on ppc64, mips, and many other architectures using
# emulation and worked as expected.
else

# For all other architectures, use only C code. No assembly.
ASM_INCLUDE=
ASM_EXCLUDE=

# End of ifdef NO_ASM.
endif

ALLCFLAGS=$(INT_FLAG) $(INLINE_FLAG) $(MATH_FLAG) $(IEEE_FLAG) $(LL_FLAG) $(MEMCPY_FLAG)
INCLUDE=\( $(ASM_INCLUDE) -name "*.c" \)
EXCLUDE=$(ASM_EXCLUDE) $(INLINE_EXCLUDE) $(MATH_EXCLUDE) $(LL_EXCLUDE)
SRCS=$(shell find $(SRC_DIRS) $(EXCLUDE) $(INCLUDE))
OBJS=$(SRCS:%=$(BUILD_DIR)/%.o)

.PHONY: clean install uninstall all

all: $(BUILD_DIR) include/tmpl_config.h $(TARGET_LIB)

include/tmpl_config.h: ./config.c $(BUILD_DIR)
	$(CC) $(ALLCFLAGS) config.c -o config.out
	./config.out
	rm -f config.out

$(TARGET_LIB): $(OBJS) include/tmpl_config.h
	$(CC) $(OBJS) $(LFLAGS) -o $@

$(BUILD_DIR)/%.c.o: %.c include/tmpl_config.h
	$(CC) $(CWARN) $(CFLAGS) $< -o $@

$(BUILD_DIR)/%.S.o: %.S include/tmpl_config.h
	$(CC) $(CWARN) $(CFLAGS) $< -o $@

$(BUILD_DIR)/%.fasm.o: %.fasm include/tmpl_config.h
	fasm $< $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)/src/bytes/
	mkdir -p $(BUILD_DIR)/src/complex/
	mkdir -p $(BUILD_DIR)/src/cyl_fresnel_optics/
	mkdir -p $(BUILD_DIR)/src/fft/
	mkdir -p $(BUILD_DIR)/src/graph_theory/
	mkdir -p $(BUILD_DIR)/src/integer/
	mkdir -p $(BUILD_DIR)/src/integration/
	mkdir -p $(BUILD_DIR)/src/interpolate/
	mkdir -p $(BUILD_DIR)/src/knots/
	mkdir -p $(BUILD_DIR)/src/math/
	mkdir -p $(BUILD_DIR)/src/numerical/
	mkdir -p $(BUILD_DIR)/src/optics/
	mkdir -p $(BUILD_DIR)/src/polynomial/
	mkdir -p $(BUILD_DIR)/src/polynomial_integer/
	mkdir -p $(BUILD_DIR)/src/ppm/
	mkdir -p $(BUILD_DIR)/src/rational/
	mkdir -p $(BUILD_DIR)/src/special_functions_complex/
	mkdir -p $(BUILD_DIR)/src/special_functions_real/
	mkdir -p $(BUILD_DIR)/src/spherical_geometry/
	mkdir -p $(BUILD_DIR)/src/sort/
	mkdir -p $(BUILD_DIR)/src/string/
	mkdir -p $(BUILD_DIR)/src/svg/
	mkdir -p $(BUILD_DIR)/src/vec2/
	mkdir -p $(BUILD_DIR)/src/vec3/
	mkdir -p $(BUILD_DIR)/src/vector_integer/
	mkdir -p $(BUILD_DIR)/src/vector_real/
	mkdir -p $(BUILD_DIR)/src/void_pointer/
	mkdir -p $(BUILD_DIR)/src/where/
	mkdir -p $(BUILD_DIR)/src/window_functions/
	mkdir -p $(BUILD_DIR)/src/assembly/fasm/
	mkdir -p $(BUILD_DIR)/src/assembly/i386/
	mkdir -p $(BUILD_DIR)/src/assembly/x86_64/
	mkdir -p $(BUILD_DIR)/src/assembly/aarch64/
	mkdir -p $(BUILD_DIR)/src/assembly/armv7l/

clean:
	rm -f *.o
	rm -rf $(BUILD_DIR)
	rm -f include/tmpl_config.h
	rm -f include/tmpl_inttype.h
	rm -f include/tmpl_limits.h
	rm -f $(TARGET_LIB)

install:
	mkdir -p /usr/local/lib/
	mkdir -p /usr/local/include/libtmpl/
	cp -r ./include /usr/local/include/libtmpl/
	cp $(TARGET_LIB) /usr/local/lib/$(TARGET_LIB)

uninstall:
	rm -f *.o
	rm -rf $(BUILD_DIR)
	rm -f include/tmpl_config.h
	rm -f include/tmpl_inttype.h
	rm -f include/tmpl_limits.h
	rm -f $(TARGET_LIB)
	rm -rf /usr/local/include/libtmpl/
	rm -f /usr/local/lib/$(TARGET_LIB)
