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
#       BUILD_STATIC:
#           Build a static library (libtmpl.a) instead of a dynamic one
#           (libtmpl.so). rss_ringoccs uses this option to simplify builds.
#           Enable with:
#               make BUILD_STATIC=1 [other-options]
#       CC:
#           C compiler to be used. Tested with:
#               gcc:   GNU C compiler.
#               clang: LLVM's C compiler.
#                   Note: Apple's version of clang has also been tested.
#               tcc:   The Tiny C Compiler.
#               pcc:   The Portable C Compiler.
#               aocc:  AMD's optimizing C Compiler.
#               icx:   Intel's C compiler.
#                   NOTE: icc not tested, but this compiler is deprecated.
#               nvc:   NVIDIA's C compiler.
#                   NOTE: The -flto option must be removed from CFLAGS and
#                         LFLAGS for nvc to compile this.
#               Enable with:
#                   make CC=c_compiler_name [other-options]
#       AR:
#           Set the archiver. This is only used if a static
#           build is begin created. Enable with:
#               make AR=archiver_name
#       ARCH:
#           Manually set the output of uname -m. The Makefile uses this to see
#           which architecture you are using in order to select the correct
#           assembly code. If you are emulating an architecture, this value
#           may not be set correctly. For example, emulating i386 on x86_64,
#           uname -m still outputs x86_64. Enabling ARCH=i386 will cause the
#           Makefile to select the correct assembly code (the code for i386,
#           instead of the code for x86_64). Note that if you disable assembly
#           code by passing NO_ASM=1 to the Makefile, this keyword has no
#           effect. Enable with:
#               make ARCH=name_of_architecture [other-options]
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
#       NO_ASM:
#           Disable all assembly code when building libtmpl. This is not
#           recommended. On several architectures, x86_64 / amd64,
#           aarch64 / arm64, ppc64le, several built-in functions like square
#           root can be used directly via assembly code. This outperforms the
#           C code by a considerable amount. If you would like to force libtmpl
#           to use only C code, enable this option. Note, if you are on an
#           architecture that libtmpl does not have assembly code for
#           (mips, for example) enabling this flag does nothing as the C code
#           will be selected automatically. Enable with:
#               make NO_ASM=1 [other-options]
#       FASM:
#           For x86_64 / amd64 you can use either GNU Assembly code (GAS) or
#           flat assembly code (FASM). GAS is the default. To use FASM, enable
#           this option. Enable with:
#               make FASM=1 [other-options]
#       USE_MEMCPY:
#           Some functions copy data by using a simple for-loop.
#           Depending on several things (compiler, libc implementation,
#           architecture), it may be faster to use a single call to the memcpy
#           function, which is found in the C standard library. Modern
#           compilers optimize the for-loop very well, and this outperforms the
#           memcpy call in many speed tests. If you would to like to force
#           use of the memcpy function, enable this option. Enable with:
#               make USE_MEMCPY=1 [other-options]
#       VOLATILE_SPLIT:
#           Force the double splitting method to use the volatile keyword.
#           Several architectures (aarch64, ppc64) require the volatile keyword
#           for the splitting method to work properly. The splitting method
#           is needed to preserve accuracy in functions like cos, sin, the
#           Fresnel integrals, and more. This Makefile has a list of known
#           architectures that require the volatile keyword to make the split
#           work. Thus far they are:
#               aarch64
#               arm64
#               armv7l
#               ppc
#               ppc64
#               ppc64le
#               riscv64
#           If your architecture is on here, no action is needed. If it is not,
#           and you are getting inaccurate results, set VOLATILE_SPLIT=1 when
#           building libtmpl. Enable with:
#               make VOLATILE_SPLIT=1 [other-options]
#       CAUTIOUS_SPLIT:
#           Force the double splitting method to use several volatile keywords.
#           This could also be called the "paranoid" method. Only one
#           architecture tested so far needs this, the i386 / x86 arch. Note
#           that x86_64 / amd64 does NOT need this. If you are getting
#           inaccurate results for cos, sin, the Fresnel integrals, or any
#           other function making use of the splitting technique, and if
#           VOLATILE_SPLIT isn't doing the trick, enable this option. Each step
#           of the split is declared volatile, which should force the compiler
#           to cooperate. This results in a slight reduction of performance,
#           but produces accurate results. Enable with:
#               make CAUTIOUS_SPLIT=1 [other-options]
#       NO_VOLATILE_SPLIT:
#           Disable the volatile keyword for the splitting technique, even if
#           you are on an architecture that requires it. This is for
#           experimenting only and should not be used in actual builds.
#           Enable with:
#               make NO_VOLATILE_SPLIT=1 [other-options]
#       EXTRA_FLAGS:
#           Any extra flags you wish to pass to the C compiler.
#           For example, with clang you can enable -Weverything via:
#               make CC=clang \
#                   EXTRA_FLAGS="-Weverything -Wno-float-equal -Wno-padded"
#           In general, enable with:
#               make EXTRA_FLAGS="flags" [other-options]

# Name of the library.
TARGET_LIB_SHARED = libtmpl.so
TARGET_LIB_STATIC = libtmpl.a

# Directory all of the .o files will be placed in.
BUILD_DIR = build

# installation prefix
prefix = /usr/local

# Location of all .c and .S files.
SRC_DIRS = src

# Compiler to be used. Override this to whatever you choose.
CC = cc

# Archiver to be used. Only needed if a static build is made.
AR = ar

# The user is allowed to specify their own flags.
EXTRA_FLAGS =

# The architecture libtmpl is being built on.
ARCH = $(shell uname -m)

# Default C flags. Note, some compilers (NVIDIA's, for example) do not
# support the flto flag. Remove whichever flags your compiler does not
# support. GCC, Clang, TCC, PCC, and AOCC handle these ones just fine.
CFLAGS = -I../ -O3 -flto -fPIC -DNDEBUG -c
LFLAGS = -O3 -fPIC -flto -DNDEBUG -shared

ifdef BUILD_STATIC
TARGET_LIB = $(TARGET_LIB_STATIC)
else
TARGET_LIB = $(TARGET_LIB_SHARED)
endif

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

# Warnings for the build. The bash script has nearly every warning for
# GCC enabled, and if clang is being used the -Weverything warning is set,
# which literally enables every warning. This helps check for standards
# compliance. This Makefile has far fewer warnings enabled.
CWARN = -Wall -Wextra -Wpedantic $(EXTRA_FLAGS)
CONFIG_FLAGS =
EXCLUDE =

# A common trick in numerical analysis with floating point number is to
# "split" a double, or long double, into two parts to preserver accuracy.
# Some architectures need the volatile keyword to prevent optimizing the split
# away, and some architectures (i386) need several volatile keywords used.
# Below is a non-exhaustive list of architectures that require the keyword.
# If you would like to force enabling of volatile, set VOLATILE_SPLIT=1.
# If you would like to force enabling of several volatile keywords, set
# CAUTIOUS_SPLIT=1. If you want to experiment and disable volatile (which is
# not recommended), set NO_VOLATILE_SPLIT=1.
ifndef NO_VOLATILE_SPLIT

# Architectures known to need the volatile keyword for splitting.
VOLATILE_SPLIT_ARCHS = aarch64 arm64 armv7l ppc ppc64 ppc64le riscv64
CAUTIOUS_SPLIT_ARCHS = i386 x86

# The user can force the volatile split flag to be enabled.
ifdef VOLATILE_SPLIT
VOLATILE_SPLIT_ARCHS += $(ARCH)
endif

# The user can also force the cautious splitting flag to be enabled.
ifdef CAUTIOUS_SPLIT
CAUTIOUS_SPLIT_ARCHS += $(ARCH)
endif

else
# Else for ifndef NO_VOLATILE_SPLIT.

# If the user requested no volatile flags at all, even if they are
# recommended, set these variables to be blank. This should be for
# experimenting only and is not recommended for actual use of libtmpl.
VOLATILE_SPLIT_ARCHS =
CAUTIOUS_SPLIT_ARCHS =

endif
# End of ifndef NO_VOLATILE_SPLIT.

# Enable splitting flags if requested, or if required. Cautious split
# gets precedence over volatile split.
ifeq ($(ARCH),$(filter $(ARCH), $(CAUTIOUS_SPLIT_ARCHS)))

CONFIG_FLAGS += -DTMPL_USE_CAUTIOUS_DOUBLE_SPLIT

else ifeq ($(ARCH),$(filter $(ARCH), $(VOLATILE_SPLIT_ARCHS)))

CONFIG_FLAGS += -DTMPL_USE_VOLATILE_DOUBLE_SPLIT

endif
# End of splitting flags.

# libtmpl will check if long long is available in config.c. If you do not want
# long long functions compiled (for example, you're on a GNU/Linux machine where
# long and long long are the same thing), set this option.
ifdef NO_LONGLONG
CONFIG_FLAGS += -DTMPL_SET_LONGLONG_FALSE
EXCLUDE += -not -name "*llong.c"
endif

# libtmpl provides its own implementation of libm. If you wish to use the
# default libm implementation (if it exists) for your system enable this option.
ifdef NO_MATH
EXCLUDE += -not -name "*_math_*.c" -not -name "*_math_*.S"
else
CONFIG_FLAGS += -DTMPL_SET_USE_MATH_TRUE
endif

# libtmpl will check if inline support is available in config.c. If you do not
# want to inline functions, set this option.
ifndef NO_INLINE
CONFIG_FLAGS += -DTMPL_SET_INLINE_TRUE
EXCLUDE += -not -name "*_no_inline_*.c"
endif

# Whether or not to use the strictly portable code, or IEEE-754 compliant code.
ifdef NO_IEEE
CONFIG_FLAGS += -DTMPL_SET_TMPL_USE_IEEE_FALSE
EXCLUDE += -not -name "*_no_ieee_*.c"
endif

# Whether to use memcpy or for-loops for copying data.
ifdef USE_MEMCPY
CONFIG_FLAGS += -DTMPL_SET_USE_MEMCPY_TRUE
endif

# Whether or not to try and find fixed-width integer data types.
ifdef NO_INT
CONFIG_FLAGS += -DTMPL_SET_NO_INT
endif

# Whether or not to force some computations to use the volatile keyword.
ifdef USE_VOLATILE
CONFIG_FLAGS += -DTMPL_USE_VOLATILE
endif

FASM_SRCS =
ASM_SRCS =

# If the user does not want to use any assembly code (that is, C only) only
# include .c files. Ignore all .S or .fasm files. For x86_64/amd64, aarch64,
# and armv7l (armhf) this is only advised if your C compiler cannot compile
# assembly code. GCC, Clang, and PCC can. I'm unsure about TCC.
ifndef NO_ASM

# amd64/x86_64 have various functions built-in, such as sqrt. Use assembly code
# if possible for performance boosts.
ifeq ($(ARCH),$(filter $(ARCH),x86_64 amd64))

# Some function for x86_64 are written in FASM, the Flat Assembler, and have
# much better times than the default C code.
ifdef FASM

FASM_SRCS = $(wildcard src/assembly/fasm/*.fasm)
EXCLUDE += $(patsubst %_x86_64.fasm,-not -name "*%.c",$(notdir $(FASM_SRCS)))

# The default is to use assembly code that GCC can understand. LLVM's clang and
# the Portable C Compiler (PCC) are also able to compile this, tested on
# Debian GNU/Linux 11 and 12.
else

ASM_SRCS = $(wildcard src/assembly/x86_64/*.S)
EXCLUDE += $(patsubst %_x86_64.S,-not -name "*%.c",$(notdir $(ASM_SRCS)))

endif
# End of ifdef FASM.

# x86 / i386 assembly is also available using GNU assembly (GAS).
else ifeq ($(ARCH),$(filter $(ARCH),i386 x86))

ASM_SRCS = $(wildcard src/assembly/i386/*.S)
EXCLUDE += $(patsubst %_i386.S,-not -name "*%.c",$(notdir $(ASM_SRCS)))

# Same idea, but for aarch64 (arm64). sqrt is also a built-in function.
else ifeq ($(ARCH),$(filter $(ARCH),aarch64 arm64))

ASM_SRCS = $(wildcard src/assembly/aarch64/*.S)
EXCLUDE += $(patsubst %_aarch64.S,-not -name "*%.c",$(notdir $(ASM_SRCS)))

# Same idea, but for armv7l (armhf). sqrt is also a built-in function.
else ifeq ($(ARCH),$(filter $(ARCH),armv7l))

ASM_SRCS = $(wildcard src/assembly/armv7l/*.S)
EXCLUDE += $(patsubst %_armv7l.S,-not -name "*%.c",$(notdir $(ASM_SRCS)))

# Lastly, PowerPC 64-bit little endian. Some assembly functions are provided.
else ifeq ($(ARCH),$(filter $(ARCH),ppc64le))

ASM_SRCS = $(wildcard src/assembly/ppc64le/*.S)
EXCLUDE += $(patsubst %_ppc64le.S,-not -name "*%.c",$(notdir $(ASM_SRCS)))

endif
# End of ifeq ($(ARCH),$(filter $(ARCH),x86_64 amd64))

endif
# End of ifndef NO_ASM.

C_SRCS = $(shell find $(SRC_DIRS) $(EXCLUDE) -name "*.c")
C_OBJS = $(C_SRCS:%=$(BUILD_DIR)/%.o)
ASM_OBJS = $(ASM_SRCS:%=$(BUILD_DIR)/%.o)
FASM_OBJS = $(FASM_SRCS:%=$(BUILD_DIR)/%.o)
OBJS = $(C_OBJS) $(ASM_OBJS) $(FASM_OBJS)

.PHONY: clean install uninstall all install-local uninstall-local help

all: $(TARGET_LIB)

include/tmpl_config.h: ./config.c
ifeq ($(CC), emcc)
	bash emscripten.sh $(CONFIG_FLAGS)
else
	$(CC) $(CONFIG_FLAGS) config.c -o config.out
	./config.out
	rm -f config.out
endif

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
	mkdir -p $(prefix)/lib/
	mkdir -p $(prefix)/include/libtmpl/
	cp -r ./include $(prefix)/include/libtmpl/
	cp $(TARGET_LIB) $(prefix)/lib/$(TARGET_LIB)

uninstall:
	rm -f *.o
	rm -rf $(BUILD_DIR)
	rm -f include/tmpl_config.h
	rm -f include/tmpl_inttype.h
	rm -f include/tmpl_limits.h
	rm -f include/tmpl_float.h
	rm -f $(TARGET_LIB)
	rm -rf $(prefix)/include/libtmpl/
	rm -f $(prefix)/lib/$(TARGET_LIB)

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

help:
	@echo "\033[0;96mBuild and install libtmpl.\n\nExecutive summary:"
	@echo "\033[0;96m\tTo build and install onto your system:"
	@echo "\033[0;96m\t\tmake -j && sudo make install"
	@echo "\033[0;96m\tTo build and install locally (current user only):"
	@echo "\033[0;96m\t\tmake -j && make install-local\n"
	@echo "\033[0;96mRecognized commands:"
	@echo "\033[0;96m\tmake:"
	@echo "\033[0;96m\t\tCompile the library. Use -j to speed this up."
	@echo "\033[0;96m\tmake install:"
	@echo "\033[0;96m\t\tInstall library into /usr/local/."
	@echo "\033[0;96m\t\tsudo privileges required."
	@echo "\033[0;96m\tmake clean:"
	@echo "\033[0;96m\t\tRemove all compiled files in this directory."
	@echo "\033[0;96m\tmake uninstall:"
	@echo "\033[0;96m\t\tRemove all compiled files from this directory and from"
	@echo "\033[0;96m\t\t/usr/local/. sudo privileges required."
	@echo "\033[0;96m\tmake install-local:"
	@echo "\033[0;96m\t\tInstall library into ~/.local/."
	@echo "\033[0;96m\t\tsudo privileges are not required."
	@echo "\033[0;96m\tmake uninstall-local:"
	@echo "\033[0;96m\t\tRemove all compiled files from this directory and from"
	@echo "\033[0;96m\t\t~/.local/. sudo privileges are not required."
	@echo "\033[0;96m\tmake help:"
	@echo "\033[0;96m\t\tPrint this message.\n"
	@echo "\033[0;96mBuild options (see comments in Makefile for more details):"
	@echo "\033[0;96m\tBUILD_STATIC:"
	@echo "\033[0;96m\t\tCreate a static libary (libtmpl.a) instead of a"
	@echo "\033[0;96m\t\tdynamic library (libtmpl.so)."
	@echo "\033[0;96m\t\tExample: make BUILD_STATIC=1"
	@echo "\033[0;96m\tCC:"
	@echo "\033[0;96m\t\tSet the C compiler. Example: make CC=gcc"
	@echo "\033[0;96m\tAR (static builds only):"
	@echo "\033[0;96m\t\tSet the archiver. Example: make AR=ar"
	@echo "\033[0;96m\tARCH:"
	@echo "\033[0;96m\t\tChange the output of uname -m. Example: make ARCH=i386"
	@echo "\033[0;96m\tOMP:"
	@echo "\033[0;96m\t\tCompile with OpenMP support. Example: make OMP=1"
	@echo "\033[0;96m\tNO_MATH:"
	@echo "\033[0;96m\t\tUse the system libm instead of libtmpl's."
	@echo "\033[0;96m\t\tExample: make NO_MATH=1"
	@echo "\033[0;96m\tNO_LONGLONG:"
	@echo "\033[0;96m\t\tDo not compile any code for long long or"
	@echo "\033[0;96m\t\tunsigned long long. Example: make NO_LONGLONG=1"
	@echo "\033[0;96m\tNO_INLINE:"
	@echo "\033[0;96m\t\tDo not inline any code. Example: make NO_INLINE=1"
	@echo "\033[0;96m\tNO_IEEE:"
	@echo "\033[0;96m\t\tDo not probe for IEEE-754 support and instead only"
	@echo "\033[0;96m\t\tonly use portable C code (NOT RECOMMENDED)."
	@echo "\033[0;96m\t\tExample: make NO_IEEE=1"
	@echo "\033[0;96m\tNO_INT:"
	@echo "\033[0;96m\t\tDo not probe for fixed-width integers and do not"
	@echo "\033[0;96m\t\tattempt any type punning (NOT RECOMMENDED)."
	@echo "\033[0;96m\t\tExample: make NO_INT=1"
	@echo "\033[0;96m\tNO_ASM:"
	@echo "\033[0;96m\t\tDo not use any assembly code."
	@echo "\033[0;96m\t\tExample: make NO_ASM=1"
	@echo "\033[0;91m\t\tNOTE:"
	@echo "\033[0;91m\t\t\tThis is NOT recommended on most architectures"
	@echo "\033[0;91m\t\t\tsince the assembly code outperforms the C code."
	@echo "\033[0;91m\t\t\tSome architectures require this to be set."
	@echo "\033[0;91m\t\t\tIf you are on armv7l and lack floating point"
	@echo "\033[0;91m\t\t\thardware support, you MUST set NO_ASM=1."
	@echo "\033[0;91m\t\t\tThis is because the Makefile assumes armv7l"
	@echo "\033[0;91m\t\t\tmachines will have hardware floats, even"
	@echo "\033[0;91m\t\t\tthough this is not required."
	@echo "\033[0;96m\tFASM (x86_64 / amd64 only):"
	@echo "\033[0;96m\t\tUse Flat Assembly (FASM) code instead of"
	@echo "\033[0;96m\t\tGNU Assembly (GAS). Example: make FASM=1"
	@echo "\033[0;96m\tUSE_MEMCPY:"
	@echo "\033[0;96m\t\tUse memcpy for copying data instead of for-loops."
	@echo "\033[0;96m\t\tExample: make USE_MEMCPY=1"
	@echo "\033[0;96m\tVOLATILE_SPLIT:"
	@echo "\033[0;96m\t\tForce double splits to use the volatile keyword."
	@echo "\033[0;96m\t\tExample: make VOLATILE_SPLIT=1"
	@echo "\033[0;96m\tCAUTIOUS_SPLIT:"
	@echo "\033[0;96m\t\tForce double splits to use several volatile keywords,"
	@echo "\033[0;96m\t\tbreaking the computation into several lines."
	@echo "\033[0;96m\t\tExample: make CAUTIOUS_SPLIT=1"
	@echo "\033[0;96m\tNO_VOLATILE_SPLIT:"
	@echo "\033[0;96m\t\tForce double splits to never use the volatile keyword"
	@echo "\033[0;96m\t\t(NOT RECOMMENDED). Example: make NO_VOLATILE_SPLIT=1"
	@echo "\033[0;96m\tEXTRA_FLAGS:"
	@echo "\033[0;96m\t\tAdd extra flags for the C compiler."
	@echo "\033[0;96m\t\tExample: make EXTRA_FLAGS=\"-Wno-float-equal\""
