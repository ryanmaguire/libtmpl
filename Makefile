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

TARGET_LIB := libtmpl.so
BUILD_DIR := ./build
SRC_DIRS := ./src

# Some functions make use of OpenMP with parallel for-loops. If using tmpyl,
# the Python wrapper for libtmpl, it is advised to compile with OpenMP support
# if possible.
ifdef OMP
CFLAGS := -fopenmp -I../ -O3 -fPIC -flto -DNDEBUG -c
LFLAGS := -fopenmp -O3 -flto -shared -lm
else
CFLAGS := -I../ -O3 -fPIC -flto -DNDEBUG -c
LFLAGS := -O3 -flto -shared -lm
endif

CWARN := -Wall -Wextra -Wpedantic

ifdef NO_INLINE
INLINE_FLAG :=
INLINE_EXCLUDE :=
else
INLINE_FLAG := -DTMPL_SET_INLINE_TRUE
INLINE_EXCLUDE := \
	-not -name "tmpl_abs_double.c" -and \
	-not -name "tmpl_abs_float.c" -and \
	-not -name "tmpl_abs_ldouble.c" -and \
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
	-not -name "tmpl_cbrt_pade_double.c" -and \
	-not -name "tmpl_cbrt_pade_float.c" -and \
	-not -name "tmpl_cbrt_pade_ldouble.c" -and \
	-not -name "tmpl_cbrt_taylor_double.c" -and \
	-not -name "tmpl_cbrt_taylor_float.c" -and \
	-not -name "tmpl_cbrt_taylor_ldouble.c" -and \
	-not -name "tmpl_complex_abs_double.c" -and \
	-not -name "tmpl_complex_abs_float.c" -and \
	-not -name "tmpl_complex_abs_ldouble.c" -and \
	-not -name "tmpl_complex_abs_squared.c" -and \
	-not -name "tmpl_complex_add.c" -and \
	-not -name "tmpl_complex_addto.c" -and \
	-not -name "tmpl_complex_quick_abs.c" -and \
	-not -name "tmpl_copysign_float.c" -and \
	-not -name "tmpl_copysign_double.c" -and \
	-not -name "tmpl_copysign_ldouble.c" -and \
	-not -name "tmpl_sin_pade_double.c" -and \
	-not -name "tmpl_sin_pade_float.c" -and \
	-not -name "tmpl_sin_pade_ldouble.c" -and \
	-not -name "tmpl_sin_pade_pi_double.c" -and \
	-not -name "tmpl_sin_pade_pi_float.c" -and \
	-not -name "tmpl_sin_pade_pi_ldouble.c" -and \
	-not -name "tmpl_sin_very_small_double.c" -and
endif

ifdef NO_MATH
MATH_FLAG :=
MATH_EXCLUDE := \
	-not -name "tmpl_abs_double.c" -and \
	-not -name "tmpl_abs_float.c" -and \
	-not -name "tmpl_abs_ldouble.c" -and \
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
MATH_FLAG := -DTMPL_SET_USE_MATH_TRUE
MATH_EXCLUDE :=
endif

ifdef NO_IEEE
IEEE_FLAG := -DTMPL_SET_TMPL_USE_IEEE_FALSE
else
IEEE_FLAG :=
endif

ifdef NO_INT
INT_FLAG := -DTMPL_SET_NO_INT
else
INT_FLAG :=
endif

uname_m := $(shell uname -m)

# If the user does not want to use any assembly code (that is, C only) only
# include .c files. Ignore all .S or .fasm files. For x86_64/amd64, aarch64,
# and armv7l (armhf) this is only advised if your C compiler cannot compile
# assembly code. GCC, Clang, and PCC can. I'm unsure about TCC.
ifdef NO_ASM
BUILTIN_EXCLUDE :=
BUILTIN_INCLUDE :=
ASM_INCLUDE :=
ASM_EXCLUDE :=

# Else for ifdef NO_ASM
# amd64/x86_64 have various functions built-in, such as sqrt. Use assembly code
# if possible for performance boosts.
else ifeq ($(uname_m),$(filter $(uname_m),x86_64 amd64))

ifdef NO_BUILTIN
BUILTIN_INCLUDE :=
BUILTIN_EXCLUDE :=
else
BUILTIN_INCLUDE := -wholename "./src/builtins/x86_64/*.S" -or
BUILTIN_EXCLUDE := \
	-not -name "tmpl_cos_double.c" -and \
	-not -name "tmpl_cos_float.c" -and \
	-not -name "tmpl_cos_ldouble.c" -and \
	-not -name "tmpl_sin_double.c" -and \
	-not -name "tmpl_sin_float.c" -and \
	-not -name "tmpl_sin_ldouble.c" -and \
	-not -name "tmpl_sincos_double.c" -and \
	-not -name "tmpl_sincos_float.c" -and \
	-not -name "tmpl_sincos_ldouble.c" -and
endif

# Some function for x86_64 are written in FASM, the Flat Assembler, and have
# much better times than the default C code.
ifdef FASM
ASM_INCLUDE := -wholename "./src/sysdeps/fasm/*.fasm" -or
ASM_EXCLUDE := \
	-not -name "tmpl_sqrt_double.c" -and \
	-not -name "tmpl_sqrt_float.c" -and

# The default is to use assembly code that GCC can understand. LLVM's clang and
# the Portable C Compiler (PCC) are also able to compile this, tested on
# Debian GNU/Linux 11.
else

ASM_INCLUDE := -wholename "./src/sysdeps/x86_64/*.S" -or
ASM_EXCLUDE := \
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

# Else for ifdef NO_ASM
# Same idea, but for aarch64 (arm64). sqrt is also a built-in function.
else ifeq ($(uname_m),$(filter $(uname_m),aarch64 arm64))

ifdef NO_BUILTIN
BUILTIN_INCLUDE :=
BUILTIN_EXCLUDE :=
else
BUILTIN_INCLUDE := -wholename "./src/builtins/x86_64/*.S" -or
BUILTIN_EXCLUDE := \
	-not -name "tmpl_cos_double.c" -and \
	-not -name "tmpl_cos_float.c" -and \
	-not -name "tmpl_cos_ldouble.c" -and \
	-not -name "tmpl_sin_double.c" -and \
	-not -name "tmpl_sin_float.c" -and \
	-not -name "tmpl_sin_ldouble.c" -and \
	-not -name "tmpl_sincos_double.c" -and \
	-not -name "tmpl_sincos_float.c" -and \
	-not -name "tmpl_sincos_ldouble.c" -and
endif

ASM_INCLUDE := -wholename "./src/sysdeps/aarch64/*.S" -or
ASM_EXCLUDE := \
	-not -name "tmpl_floor_double.c" -and \
	-not -name "tmpl_floor_float.c" -and \
	-not -name "tmpl_floor_ldouble.c" -and \
	-not -name "tmpl_sqrt_double.c" -and \
	-not -name "tmpl_sqrt_float.c" -and \
	-not -name "tmpl_sqrt_ldouble.c" -and

# Else for ifdef NO_ASM
# Same idea, but for armv7l (armhf). sqrt is also a built-in function.
else ifeq ($(uname_m),$(filter $(uname_m),armv7l))

BUILTIN_EXCLUDE :=
BUILTIN_INCLUDE :=
ASM_INCLUDE := -wholename "sysdeps/armv7l/*.S"
ASM_EXCLUDE :=
	$(shell find $(SRC_DIRS) $(EXCLUDE) \
	-not -name "tmpl_sqrt_double.c" -and \
	-not -name "tmpl_sqrt_float.c" -and \
	-not -name "tmpl_sqrt_ldouble.c" -and \
	\( -name "*.c" -or -name "*armv7l.S" \))

# Else for ifeq ($(uname_p),x86_64). Only amd64/x86_64 and aarch64/arm7l have
# assembly code support. This may change in the future. The rest of the C
# code has been tested on ppc64, mips, and many other architectures using
# emulation and worked as expected.
else

# For all other architectures, use only C code. No assembly.
BUILTIN_EXCLUDE :=
BUILTIN_INCLUDE :=
ASM_INCLUDE :=
ASM_EXCLUDE :=

# End of ifdef NO_ASM.
endif

ALLINCLUDE := \( $(ASM_INCLUDE) $(BUILTIN_INCLUDE) -name "*.c" \)
EXCLUDE := $(ASM_EXCLUDE) $(BUILTIN_EXCLUDE) $(INLINE_EXCLUDE) $(MATH_EXCLUDE)
SRCS := $(shell find $(SRC_DIRS) $(EXCLUDE) $(ALLINCLUDE))

OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

ALLCFLAGS := $(INT_FLAG) $(INLINE_FLAG) $(MATH_FLAG) $(IEEE_FLAG)

.PHONY: clean install uninstall all

all: $(BUILD_DIR) include/tmpl_config.h $(TARGET_LIB)

include/tmpl_config.h: ./config.c
	$(CC) $(ALLCFLAGS) config.c -o config.out
	./config.out
	rm -f config.out

$(TARGET_LIB): $(OBJS)
	$(CC) $(OBJS) $(LFLAGS) -o $@

$(BUILD_DIR)/%.c.o: %.c
	$(CC) $(CWARN) $(CFLAGS) $< -o $@

$(BUILD_DIR)/%.S.o: %.S
	$(CC) $(CWARN) $(CFLAGS) $< -o $@

$(BUILD_DIR)/%.fasm.o: %.fasm
	fasm $< $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)/src/bytes/
	mkdir -p $(BUILD_DIR)/src/complex/
	mkdir -p $(BUILD_DIR)/src/fft/
	mkdir -p $(BUILD_DIR)/src/graph_theory/
	mkdir -p $(BUILD_DIR)/src/interpolate/
	mkdir -p $(BUILD_DIR)/src/knots/
	mkdir -p $(BUILD_DIR)/src/math/
	mkdir -p $(BUILD_DIR)/src/number_theory/
	mkdir -p $(BUILD_DIR)/src/numerical/
	mkdir -p $(BUILD_DIR)/src/optics/
	mkdir -p $(BUILD_DIR)/src/polynomial/
	mkdir -p $(BUILD_DIR)/src/ppm/
	mkdir -p $(BUILD_DIR)/src/rational/
	mkdir -p $(BUILD_DIR)/src/special_functions/
	mkdir -p $(BUILD_DIR)/src/spherical_geometry/
	mkdir -p $(BUILD_DIR)/src/string/
	mkdir -p $(BUILD_DIR)/src/svg/
	mkdir -p $(BUILD_DIR)/src/vec2/
	mkdir -p $(BUILD_DIR)/src/vec3/
	mkdir -p $(BUILD_DIR)/src/vector/
	mkdir -p $(BUILD_DIR)/src/void_pointer/
	mkdir -p $(BUILD_DIR)/src/window_functions/
ifdef FASM
	mkdir -p $(BUILD_DIR)/src/sysdeps/fasm/
ifndef NO_BUILTIN
	mkdir -p $(BUILD_DIR)/src/builtins/x86_64/
endif
else ifndef NO_ASM
ifeq ($(uname_m),$(filter $(uname_m),x86_64 amd64))
	mkdir -p $(BUILD_DIR)/src/sysdeps/x86_64/
ifndef NO_BUILTIN
	mkdir -p $(BUILD_DIR)/src/builtins/x86_64/
endif
else ifeq ($(uname_m),$(filter $(uname_m),aarch64 arm64))
	mkdir -p $(BUILD_DIR)/src/sysdeps/aarch64/
ifndef NO_BUILTIN
	mkdir -p $(BUILD_DIR)/src/builtins/aarch64/
endif
else ifeq ($(uname_m),$(filter $(uname_m),armv7l))
	mkdir -p $(BUILD_DIR)/src/sysdeps/armv7l/
endif
endif

clean:
	rm -rf $(BUILD_DIR)
	rm -f include/tmpl_config.h
	rm -f include/tmpl_integer.h
	rm -f $(TARGET_LIB)

install:
	mkdir -p /usr/local/include/libtmpl/
	cp -r ./include/ /usr/local/include/libtmpl/
	cp $(TARGET_LIB) /usr/local/lib/$(TARGET_LIB)

uninstall:
	rm -rf $(BUILD_DIR)
	rm -f include/tmpl_config.h
	rm -f include/tmpl_integer.h
	rm -f $(TARGET_LIB)
	rm -rf /usr/local/include/libtmpl/
	rm -f /usr/local/lib/$(TARGET_LIB)

-include $(DEPS)

