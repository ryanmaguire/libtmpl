################################################################################
#                                  LICENSE                                     #
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

CFLAGS := $(CFLAGS) -I../ -O3 -fPIC -flto -DNDEBUG -c
LFLAGS := -O3 -flto -shared -lm

# Some functions make use of OpenMP with parallel for-loops. If using tmpyl,
# the Python wrapper for libtmpl, it is advised to compile with OpenMP support
# if possible.
ifdef OMP
overide CFLAGS := -fopenmp $(CFLAGS)
overide LFLAGS := -fopenmp $(LFLAGS)
endif

ifdef NO_INLINE
INLINE_EXCLUDE :=
else
INLINE_EXCLUDE := -not -name "tmpl_abs_double.c" -and
endif

uname_m := $(shell uname -m)

# amd64/x86_64 have various functions built-in, such as sqrt. Use assembly code
# if possible for performance boosts.
ifeq ($(uname_m),$(filter $(uname_m),x86_64 amd64))

# If the user does not want to use any assembly code (that is, C only) only
# include .c files. Ignore all .S or .fasm files. For x86_64 computers this is
# only advised if you do not have FASM or your C compiler cannot compile
# assembly code. GCC, Clang, and PCC can. I'm unsure about TCC.
ifdef NO_ASM
SRCS := $(shell find $(SRC_DIRS) $(INLINE_EXCLUDE) -name "*.c")

# Some function for x86_64 are written in FASM, the Flat Assembler, and have
# much better times than the default C code.
else ifdef FASM
SRCS := \
	$(shell find $(SRC_DIRS) $(INLINE_EXCLUDE) \
	-not -name "tmpl_sqrt_double.c" -and \
	-not -name "tmpl_sqrt_float.c" -and \
	\( -name "*.c" -or -name "*x86_64.fasm" \))

# The default is to use assembly code that GCC can understand. LLVM's clang and
# the Portable C Compiler (PCC) are also able to compile this, tested on
# Debian GNU/Linux 11.
else
SRCS := \
	$(shell find $(SRC_DIRS) $(INLINE_EXCLUDE) \
	-not -name "tmpl_sqrt_double.c" -and \
	-not -name "tmpl_sqrt_float.c" -and \
	-not -name "tmpl_sqrt_ldouble.c" -and \
	\( -name "*.c" -or -name "*x86_64.S" \))
endif
# End of ifdef NO_ASM.

# Else for ifeq ($(uname_p),x86_64). Currently, only x86_64 assembly code is
# supported. This may change in the future. The rest of the C code has been
# tested on arm64, ppc64, mips, and many other architectures using emulation
# and worked as expected.
else
# Else for ifeq ($(uname_m),$(filter $(uname_m),x86_64 amd64))

SRCS := $(shell find $(SRC_DIRS) $(INLINE_EXCLUDE) -name "*.c")

endif
# End of ifeq ($(uname_m),$(filter $(uname_m),x86_64 amd64))

OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

.PHONY: clean install uninstall all

all: include/tmpl_inline.h include/tmpl_endianness.h $(TARGET_LIB)

include/tmpl_endianness.h: ./det_end.c
	$(CC) det_end.c -o det_end.out
	./det_end.out
	rm -f det_end.out

include/tmpl_inline.h: ./det_inline.c
	$(CC) det_inline.c -o det_inline.out
	./det_inline.out
	rm -f det_inline.out

$(TARGET_LIB): $(OBJS)
	$(CC) $(OBJS) $(LFLAGS) -o $@

$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) $< -o $@

$(BUILD_DIR)/%.S.o: %.S
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) $< -o $@

$(BUILD_DIR)/%.fasm.o: %.fasm
	mkdir -p $(dir $@)
	fasm $< $@

clean:
	rm -rf $(BUILD_DIR)
	rm -f include/tmpl_endianness.h

install:
	mkdir -p /usr/local/include/libtmpl/include/
	cp ./include/*.h /usr/local/include/libtmpl/include/
	cp $(TARGET_LIB) /usr/local/lib/$(TARGET_LIB)

uninstall:
	rm -rf $(BUILD_DIR)
	rm -f include/tmpl_endianness.h
	rm -rf /usr/local/include/libtmpl/
	rm -f /usr/local/lib/$(TARGET_LIB)

-include $(DEPS)

