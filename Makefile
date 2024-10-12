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
TARGET_LIB_SHARED := libtmpl.so
TARGET_LIB_STATIC := libtmpl.a
ifdef BUILD_STATIC
TARGET_LIB := $(TARGET_LIB_STATIC)
AR ?= ar
else
TARGET_LIB := $(TARGET_LIB_SHARED)
endif

# Directory all of the .o files will be placed in.
BUILD_DIR := ./build

# Location of all .c and .S files.
SRC_DIRS := ./src

# Compiler to be used. Override this to whatever you choose.
CC ?= cc

CFLAGS := -I../ -O3 -fPIC -flto -DNDEBUG -c
LFLAGS := -O3 -fPIC -flto -DNDEBUG -shared

VOLATILE_SPLIT_ARCHS = aarch64 arm64 armv7l ppc ppc64 ppc64le riscv64
CAUTIOUS_SPLIT_ARCHS = i386 x86

# Some functions use omp with for-loops (void_pointer functions), if available.
ifdef OMP
CFLAGS += -fopenmp
LFLAGS += -fopenmp
endif

# Some old functions still call math.h. This will be replaced soon.
ifdef NO_MATH
LFLAGS += -lm
else
LFLAGS += -lm
endif

CWARN := -Wall -Wextra -Wpedantic

ifdef EXTRA_FLAGS
CWARN += $(EXTRA_FLAGS)
endif

CONFIG_FLAGS :=
EXCLUDE :=

# libtmpl will check if long long is available in config.c. If you do not want
# long long functions compiled (for example, you're on a GNU/Linux machine where
# long and long long are the same thing), set this option.
ifdef NO_LONGLONG
CONFIG_FLAGS += -DTMPL_SET_LONGLONG_FALSE
EXCLUDE += -not -name "*_llong.c" -and -not -name "*_ullong.c" -and
endif

# libtmpl provides its own implementation of libm. If you wish to use the
# default libm implementation (if it exists) for your system enable this option.
ifdef NO_MATH
EXCLUDE += -not -name "*_math_*.c" -and
else
CONFIG_FLAGS += -DTMPL_SET_USE_MATH_TRUE
endif

# libtmpl will check if inline support is available in config.c. If you do not
# want to inline functions, set this option.
ifndef NO_INLINE
CONFIG_FLAGS += -DTMPL_SET_INLINE_TRUE
EXCLUDE += -not -name "*_no_inline_*.c" -and
endif

# Whether or not to use the strictly portable code, of IEEE-754 compliant code.
ifdef NO_IEEE
CONFIG_FLAGS += -DTMPL_SET_TMPL_USE_IEEE_FALSE
endif

ifdef USE_MEMCPY
CONFIG_FLAGS += -DTMPL_SET_USE_MEMCPY_TRUE
endif

# Whether or not to try and find fixed-width integer data types.
ifdef NO_INT
CONFIG_FLAGS += -DTMPL_SET_NO_INT
endif

ASM_INCLUDE :=

# If the user does not want to use any assembly code (that is, C only) only
# include .c files. Ignore all .S or .fasm files. For x86_64/amd64, aarch64,
# and armv7l (armhf) this is only advised if your C compiler cannot compile
# assembly code. GCC, Clang, and PCC can. I'm unsure about TCC.
ifndef NO_ASM

# The architecture libtmpl is being built on.
ifndef ARCH
uname_m := $(shell uname -m)
else
uname_m := $(ARCH)
endif

# Else for ifdef NO_ASM
# amd64/x86_64 have various functions built-in, such as sqrt. Use assembly code
# if possible for performance boosts.
ifeq ($(uname_m),$(filter $(uname_m),x86_64 amd64))

# Some function for x86_64 are written in FASM, the Flat Assembler, and have
# much better times than the default C code.
ifdef FASM
ASM_INCLUDE += -wholename "./src/assembly/fasm/*.fasm" -or
EXCLUDE +=\
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
-not -name "tmpl_floor_math_double.c" -and \
-not -name "tmpl_floor_math_float.c" -and \
-not -name "tmpl_floor_math_ldouble.c" -and

# The default is to use assembly code that GCC can understand. LLVM's clang and
# the Portable C Compiler (PCC) are also able to compile this, tested on
# Debian GNU/Linux 11.
else

ASM_INCLUDE += -wholename "./src/assembly/x86_64/*.S" -or
EXCLUDE +=\
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
-not -name "tmpl_floor_math_double.c" -and \
-not -name "tmpl_floor_math_float.c" -and \
-not -name "tmpl_floor_math_ldouble.c" -and
endif
# End of ifdef FASM.

else ifeq ($(uname_m),$(filter $(uname_m),i386 x86))

ASM_INCLUDE += -wholename "./src/assembly/i386/*.S" -or
EXCLUDE +=\
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
-not -name "tmpl_floor_math_double.c" -and \
-not -name "tmpl_floor_math_float.c" -and \
-not -name "tmpl_floor_math_ldouble.c" -and

# Same idea, but for aarch64 (arm64). sqrt is also a built-in function.
else ifeq ($(uname_m),$(filter $(uname_m),aarch64 arm64))

ASM_INCLUDE += -wholename "./src/assembly/aarch64/*.S" -or
EXCLUDE +=\
-not -name "tmpl_floor_math_double.c" -and \
-not -name "tmpl_floor_math_float.c" -and \
-not -name "tmpl_sqrt_double.c" -and \
-not -name "tmpl_sqrt_float.c" -and

# Same idea, but for armv7l (armhf). sqrt is also a built-in function.
else ifeq ($(uname_m),$(filter $(uname_m),armv7l))

ASM_INCLUDE += -wholename "./src/assembly/armv7l/*.S" -or
EXCLUDE +=\
-not -name "tmpl_sqrt_double.c" -and \
-not -name "tmpl_sqrt_float.c" -and \
-not -name "tmpl_sqrt_ldouble.c" -and

else ifeq ($(uname_m),$(filter $(uname_m),ppc64le))

ASM_INCLUDE += -wholename "./src/assembly/ppc64le/*.S" -or
EXCLUDE +=\
-not -name "tmpl_trailing_zeros_char.c" -and \
-not -name "tmpl_trailing_zeros_int.c" -and \
-not -name "tmpl_trailing_zeros_long.c" -and \
-not -name "tmpl_trailing_zeros_short.c" -and \
-not -name "tmpl_trailing_zeros_uchar.c" -and \
-not -name "tmpl_trailing_zeros_uint.c" -and \
-not -name "tmpl_trailing_zeros_ulong.c" -and \
-not -name "tmpl_trailing_zeros_ushort.c" -and \
-not -name "tmpl_floor_math_double.c" -and \
-not -name "tmpl_floor_math_float.c" -and \
-not -name "tmpl_sqrt_double.c" -and \
-not -name "tmpl_sqrt_float.c" -and

endif
# End of ifeq ($(uname_m),$(filter $(uname_m),x86_64 amd64))

endif
# End of ifndef NO_ASM.

ifeq ($(uname_m),$(filter $(uname_m), $(VOLATILE_SPLIT_ARCHS)))

CONFIG_FLAGS += -DTMPL_USE_VOLATILE_DOUBLE_SPLIT

else ifeq ($(uname_m),$(filter $(uname_m), $(CAUTIOUS_SPLIT_ARCHS)))

CONFIG_FLAGS += -DTMPL_USE_CAUTIOUS_DOUBLE_SPLIT

endif


INCLUDE := \( $(ASM_INCLUDE) -name "*.c" \)
SRCS := $(shell find $(SRC_DIRS) $(EXCLUDE) $(INCLUDE))
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

.PHONY: clean install uninstall all install-local uninstall-local

all: $(TARGET_LIB)

include/tmpl_config.h: ./config.c
	$(CC) $(CONFIG_FLAGS) config.c -o config.out
	./config.out
	rm -f config.out

$(TARGET_LIB_SHARED): $(OBJS) include/tmpl_config.h
	@echo "Building libtmpl.so ..."
	@-$(CC) $(OBJS) $(LFLAGS) -o $@

$(TARGET_LIB_STATIC): $(OBJS) include/tmpl_config.h
	@echo "Building libtmpl.a ..."
	@-$(AR) rcs $@ $(OBJS)

$(BUILD_DIR)/%.c.o: %.c include/tmpl_config.h
	@mkdir -p $(@D)
	$(CC) $(CWARN) $(CFLAGS) $< -o $@

$(BUILD_DIR)/%.S.o: %.S include/tmpl_config.h
	@mkdir -p $(@D)
	$(CC) $(CWARN) $(CFLAGS) $< -o $@

$(BUILD_DIR)/%.fasm.o: %.fasm include/tmpl_config.h
	@mkdir -p $(@D)
	fasm $< $@

clean:
	rm -f *.o
	rm -rf $(BUILD_DIR)
	rm -f include/tmpl_config.h
	rm -f include/tmpl_inttype.h
	rm -f include/tmpl_limits.h
	rm -f include/tmpl_float.h
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
	rm -f include/tmpl_float.h
	rm -f $(TARGET_LIB)
	rm -rf /usr/local/include/libtmpl/
	rm -f /usr/local/lib/$(TARGET_LIB)

install-local:
	mkdir -p $(HOME)/.local/include/libtmpl/
	mkdir -p $(HOME)/.local/lib/
	cp -r ./include $(HOME)/.local/include/libtmpl/
	cp $(TARGET_LIB) $(HOME)/.local/lib/$(TARGET_LIB)

uninstall-local:
	rm -f *.o
	rm -rf $(BUILD_DIR)
	rm -f include/tmpl_config.h
	rm -f include/tmpl_inttype.h
	rm -f include/tmpl_limits.h
	rm -f include/tmpl_float.h
	rm -f $(TARGET_LIB)
	rm -rf $(HOME)/.local/include/libtmpl/
	rm -f $(HOME)/.local/lib/$(TARGET_LIB)
