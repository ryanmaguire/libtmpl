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
#       BUILD_SHARED_LIBS:
#           Build a shared object (libtmpl.so) instead of a static one
#           (libtmpl.a). Enable with:
#               make BUILD_SHARED_LIBS=ON [other-options]
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
#           Enable with:
#               make CC=c_compiler_name [other-options]
#       AR:
#           Set the archiver. This is only used if a static
#           build is being created. Enable with:
#               make AR=archiver_name [other-options]
#       ARCH:
#           Manually set the output of uname -m. The Makefile uses this to see
#           which architecture you are using in order to select the correct
#           assembly code. If you are emulating an architecture, this value
#           may not be set correctly. For example, emulating i386 on x86_64,
#           uname -m still outputs x86_64. Enabling ARCH=i386 will cause the
#           Makefile to select the correct assembly code (the code for i386,
#           instead of the code for x86_64). Note that if you disable assembly
#           code by passing NO_ASM=ON to the Makefile, this keyword has no
#           effect. Enable with:
#               make ARCH=name_of_architecture [other-options]
#       DEBUG_BUILD:
#           Compile with debug symbols. Enable with:
#               make DEBUG_BUILD=ON [other-options]
#       SIMD_FAST_MATH:
#           Enable very aggressive optimizations and use OpenMP to create SIMD
#           versions of several of libtmpl's functions. This option is only
#           supported by a few compilers (GCC 15+, for example). It enables
#           the -ffast-math, -march=native, and -fopenmp-simd flags, and
#           requires C23 attributes to protect certain functions like 2Sum and
#           2Prod from these aggressive compiler options. With appropriate
#           hardware, this option can double the speed of some functions.
#           Enable with:
#               make SIMD_FAST_MATH=ON [other-options]
#           NOTE:
#               Library functions usually have 1 ULP error.
#               The vectorized versions have roughly twice the amount
#               of error, about 2-4 ULP.
#       USE_OMP:
#           Set OpenMP flags. Useful if you want to build libtmpyl, the Python
#           wrapper for libtmpl, and use with numpy arrays for parallel
#           computing. Enable with:
#               make USE_OMP=ON [other-options]
#       NO_LTO:
#           Disable the -flto flag (link-time optimization). Some compilers
#           do not support -flto and hence this needs to be enabled. For
#           NVIDIA's C compiler (nvc) this option is automatically set for you.
#           Enable with:
#               make NO_LTO=ON [other-options]
#       NO_MATH:
#           Do not use libtmpl's implementation of libm, the C standard
#           mathematical library. You must have C99 or higher support if you
#           wish to enable this. The original C89 standard does not require
#           float and long double versions of various functions, whereas
#           libtmpl makes use of these.
#               make NO_MATH=ON [other-options]
#       NO_LONGLONG:
#           libtmpl provides many functions for integer data types. The config.c
#           file will examine the __STDC_VERSION__ macro to check if long long
#           is available. If you do not wish to build long long functions at
#           all, set this option (for example, you're on a GNU/Linux machine
#           where the long and long long data types are the same). Enable with:
#               make NO_LONGLONG=ON [other-options]
#       NO_INLINE:
#           libtmpl allows many smaller functions to be inlined, resulting in
#           significant speed boosts in several cases (tmpl_Double_Abs is about
#           2x faster when inlined, for example). The config.c file will check
#           the __STDC_VERSION__ macro to see if inline support is available.
#           If you do not wish to use inlined code, set this option. Enable via:
#               make NO_INLINE=ON [other-options]
#       ALWAYS_INLINE:
#           Enable the C23 attributes [[gnu::always_inline]] or
#           [[clang::always_inline]] for inlined functions. Your compiler
#           must support C23 attributes if you want to use this.
#           Enable with:
#               make ALWAYS_INLINE=ON [other-options]
#       NATIVE:
#           Enable native CPU instructions if the compiler supports them.
#           Enable with:
#               make NATIVE=ON [other-options]
#       NO_IEEE:
#           Many functions use unions to take advantage of the IEEE-754
#           format for floating-point numbers. This behavior is implementation
#           defined in C89, but every compiler I know supports it. Indeed, every
#           implementation of libm that I am aware of makes use of this trick.
#           The config.c file will check if you have IEEE-754 support and can
#           access the bits using a union. If you wish to force the portable
#           code to be used, set this option. Note, the portable algorithms are
#           significantly slower, in some cases about 10x or worse. Note, in
#           C11 and C23, type-punning via unions is well-defined behavior.
#               make NO_IEEE=ON [other-options]
#       NO_INT:
#           It is sometimes useful to have fixed-width (8, 16, 32, and 64) bit
#           integers. The C standard does not require these widths be available
#           but rather specifies the minimum widths allowed by certain data
#           types. The config.c file will try to find the widths of various
#           integer types. To skip this, set this option. Enable with:
#               make NO_INT=ON [other-options]
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
#               make NO_ASM=ON [other-options]
#       NO_INLINE_ASM:
#           Some of the functions in src/assembly/ are implemented twice:
#           once as an assembly file (.S), and once as a C file that uses
#           GNU-style inline assembly (.c). If your compiler supports GNU inline
#           assembly, the .c files are used, since with link-time optimization
#           they can be inlined across translation units. To use the .S files
#           instead, enable this option. SIMD_FAST_MATH always uses the .S
#           files, and NO_ASM disables both. Enable with:
#               make NO_INLINE_ASM=ON [other-options]
#       USE_FASM:
#           For x86_64 / amd64 you can use either GNU Assembly code (GAS) or
#           flat assembly code (FASM). GAS is the default. To use FASM, enable
#           this option. Enable with:
#               make USE_FASM=ON [other-options]
#       USE_MEMCPY:
#           Some functions copy data by using a simple for-loop.
#           Depending on several things (compiler, libc implementation,
#           architecture), it may be faster to use a single call to the memcpy
#           function, which is found in the C standard library. Modern
#           compilers optimize the for-loop very well, and this outperforms the
#           memcpy call in many speed tests. If you would like to force
#           use of the memcpy function, enable this option. Enable with:
#               make USE_MEMCPY=ON [other-options]
#       USE_VOLATILE:
#           Set the TMPL_VOLATILE macro to "volatile" instead of being empty.
#           This may be necessary for libtmpl's double-double arithmetic
#           routines to work properly. If your compiler supports C23 attributes
#           and implements the [[gnu::optimize(...)]] attribute, then you do
#           not need to enable this option. The necessary functions will set
#           the "no-associative-math" and "fp-contract=off" options to prevent
#           aggressive optimizations from ruining them. Enable with:
#               make USE_VOLATILE=ON [other-options]
#       EXTRA_FLAGS:
#           Any extra flags you wish to pass to the C compiler.
#           For example, with clang you can enable -Weverything via:
#               make CC=clang \
#                   EXTRA_FLAGS="-Weverything -Wno-float-equal -Wno-padded"
#           In general, enable with:
#               make EXTRA_FLAGS="flags" [other-options]

# Default options.
BUILD_SHARED_LIBS = OFF
DEBUG_BUILD = OFF
SIMD_FAST_MATH = OFF
USE_OMP = OFF
NO_LTO = OFF
NO_MATH = OFF
NO_LONGLONG = OFF
NO_INLINE = OFF
ALWAYS_INLINE = ON
NATIVE = ON
NO_IEEE = OFF
NO_INT = OFF
NO_ASM = OFF
NO_INLINE_ASM = OFF
USE_FASM = OFF
USE_MEMCPY = OFF
USE_VOLATILE = OFF

# Name of the library.
TARGET_LIB_SHARED = libtmpl.so
TARGET_LIB_STATIC = libtmpl.a

# Directory all of the .o files will be placed in.
BUILD_DIR = build

# installation prefix
prefix = /usr/local

# Location of all .c and .S files.
SRC_DIR = src

# Compiler to be used. Override this to whatever you choose.
CC = cc

# Archiver to be used. Only needed if a static build is made.
AR = ar

# The architecture libtmpl is being built on.
ARCH = $(shell uname -m)

# The user is allowed to specify their own flags.
EXTRA_FLAGS =

# Warnings for the build. The bash script has nearly every warning for
# GCC enabled, and if clang is being used the -Weverything warning is set,
# which literally enables every warning. This helps check for standards
# compliance. This Makefile has far fewer warnings enabled.
CWARN = -Wall -Wextra -Wpedantic $(EXTRA_FLAGS)

# Config flags and exclude flags depends on the architecture.
# We'll set these later when we examine the ARCH variable.
CONFIG_FLAGS = $(EXTRA_FLAGS)
EXCLUDE =

# If the compiler supports GNU inline assembly, then various .S files in
# src/assembly/ will be replaced by their .c counterparts (unless NO_INLINE_ASM
# is set). This allows cross-translation unit inlining when link time
# optimization (LTO) is enabled. By default we do not assume GNU inline assembly
# is supported. This will be checked later in the Makefile.
EXCLUDE += ! -path "$(SRC_DIR)/assembly/*"

# Default C flags. GCC, Clang, TCC, PCC, and AOCC handle these ones just fine.
ifneq ($(filter $(DEBUG_BUILD), ON on TRUE true 1),)
CFLAGS = -I../ -g -fPIC -c
LFLAGS = -fPIC -g -shared
else ifdef SUNCC
CFLAGS = -I../ -xO5 -xipo -KPIC -DNDEBUG -c
LFLAGS = -xO5 -xipo -KPIC -G
CONFIG_FLAGS += -xO5 -KPIC
else
CFLAGS = -I../ -O3 -flto -fPIC -DNDEBUG -c
LFLAGS = -O3 -fPIC -flto -DNDEBUG -shared
CONFIG_FLAGS += -O3 -fPIC
endif

# NVIDIA's C compiler (nvc) does not support the -flto flag.
ifeq ($(CC), nvc)
CFLAGS := $(filter-out -flto, $(CFLAGS))
LFLAGS := $(filter-out -flto, $(LFLAGS))
endif

ifneq ($(filter $(NO_LTO), ON on TRUE true 1),)
CFLAGS := $(filter-out -flto, $(CFLAGS))
LFLAGS := $(filter-out -flto, $(LFLAGS))
endif

ifneq ($(filter $(BUILD_SHARED_LIBS), ON on TRUE true 1),)
TARGET_LIB = $(TARGET_LIB_SHARED)
else
TARGET_LIB = $(TARGET_LIB_STATIC)
endif

# Some functions use omp with for-loops (void_pointer functions), if available.
ifneq ($(filter $(USE_OMP), ON on TRUE true 1),)
CFLAGS += -fopenmp
LFLAGS += -fopenmp
endif

# If libtmpl's libm implementation is not being used, we need to link with libm.
ifneq ($(filter $(NO_MATH), ON on TRUE true 1),)
LFLAGS += -lm
endif

# libtmpl will check if long long is available in config.c. If you do not want
# long long functions compiled (for example, you're on a GNU/Linux machine where
# long and long long are the same thing), set this option.
ifneq ($(filter $(NO_LONGLONG), ON on TRUE true 1),)
CONFIG_FLAGS += -DTMPL_SET_LONGLONG_FALSE
EXCLUDE += ! -name "*llong.c" ! -name "*llong*.S"
endif

# libtmpl provides its own implementation of libm. If you wish to use the
# default libm implementation (if it exists) for your system enable this option.
ifneq ($(filter $(NO_MATH), ON on TRUE true 1),)
EXCLUDE += ! -name "*_math_*.c" ! -name "*_math_*.S"
else
CONFIG_FLAGS += -DTMPL_SET_USE_MATH_TRUE
endif

# libtmpl will check if inline support is available in config.c. If you do not
# want to inline functions, set this option.
ifneq ($(filter $(NO_INLINE), OFF off FALSE false 0),)
CONFIG_FLAGS += -DTMPL_SET_INLINE_TRUE
EXCLUDE += ! -name "*_no_inline_*.c"
endif

# Users may wish to force inlining functions. The config.c file will only do
# this if the appropriate macro is set.
ifneq ($(filter $(ALWAYS_INLINE), ON on TRUE true 1),)
CONFIG_FLAGS += -DTMPL_SET_ALWAYS_INLINE_TRUE
endif

# Whether or not to use the strictly portable code, or IEEE-754 compliant code.
ifneq ($(filter $(NO_IEEE), ON on TRUE true 1),)
CONFIG_FLAGS += -DTMPL_SET_TMPL_USE_IEEE_FALSE
endif

# Whether to use memcpy or for-loops for copying data.
ifneq ($(filter $(USE_MEMCPY), ON on TRUE true 1),)
CONFIG_FLAGS += -DTMPL_SET_USE_MEMCPY_TRUE
endif

# Whether or not to try and find fixed-width integer data types.
ifneq ($(filter $(NO_INT), ON on TRUE true 1),)
CONFIG_FLAGS += -DTMPL_SET_NO_INT
endif

# Whether or not to force some computations to use the volatile keyword.
ifneq ($(filter $(USE_VOLATILE), ON on TRUE true 1),)
CONFIG_FLAGS += -DTMPL_USE_VOLATILE
endif

# Commands for compiling a small test program to check for GNU inline assembly.
INLINE_ASM_FILE = ./config/tmpl_config_determine_inline_assembly_support.c
DET_INLINE_ASM_CMD = $(CC) -c -o /dev/null $(INLINE_ASM_FILE) >/dev/null 2>&1

# Compilers like GCC and Clang support native CPU tuning. This is usually
# enabled via -march=native or -mcpu=native. The exact flag depends on the
# architecture being used.
NATIVE_FLAGS := $(shell                                                        \
    if $(CC) -march=native -E -x c - </dev/null >/dev/null 2>&1; then          \
        echo "-march=native";                                                  \
    elif $(CC) -mcpu=native -E -x c - </dev/null >/dev/null 2>&1; then         \
        echo "-mcpu=native";                                                   \
    fi                                                                         \
)

# Some math routines can be vectorized. Required SIMD instructions and OpenMP.
# Currently only GCC and Clang are supported when using this option.
# Other compilers may work with this option, so long as they support
# -ffast-math, -march / -mcpu, and -fopenmp-simd.
ifneq ($(filter $(SIMD_FAST_MATH), ON on TRUE true 1),)

CFLAGS += $(NATIVE_FLAGS) -ffast-math -fopenmp-simd
LFLAGS += $(NATIVE_FLAGS) -fopenmp-simd
CONFIG_FLAGS += -DTMPL_SET_USE_SIMD_FAST_MATH_TRUE

# The user may want to use native instructions without
# enabling SIMD vectorization.
else ifneq ($(filter $(NATIVE), ON on TRUE true 1),)
CFLAGS += $(NATIVE_FLAGS)
LFLAGS += $(NATIVE_FLAGS)
CONFIG_FLAGS += $(NATIVE_FLAGS)
endif

FASM_SRCS =
ASM_SRCS =
INLINE_ASM_SRCS =

# If the user does not want to use any assembly code (that is, C only) only
# include .c files. Ignore all .S or .fasm files. For x86_64/amd64, aarch64,
# and armv7l (armhf) this is only advised if your C compiler cannot handle
# assembly code. GCC, Clang, and PCC can. TCC cannot.
ifneq ($(filter $(NO_ASM), OFF off FALSE false 0),)

# Various architectures have assembly support for functions that map directly
# to instructions, like sqrt -> sqrtsd on x86-64. The architecture that the
# user is running is detected via "uname -m". Equivalent architectures may
# return different values with this command, such as amd64 and x86_64 for the
# x86-64 architecture, or aarch64 / arm64 for the armv8 architecture. The
# variables below allow us to generically select the correct assembly code.
ASM_ARCH_x86_64 := x86_64
ASM_ARCH_amd64 := x86_64
ASM_ARCH_i386 := i386
ASM_ARCH_i686 := i386
ASM_ARCH_x86 := i386
ASM_ARCH_aarch64 := aarch64
ASM_ARCH_arm64 := aarch64
ASM_ARCH_armv7l := armv7l
ASM_ARCH_ppc64 := ppc64
ASM_ARCH_ppc64le := ppc64
ASM_ARCH_s390x := s390x
ASM_ARCH := $(ASM_ARCH_$(ARCH))

# FASM is only available for x86_64 / amd64. It is ignored everywhere else.
ifeq ($(ASM_ARCH), x86_64)
ifneq ($(filter $(USE_FASM), ON on TRUE true 1),)
USE_FASM_ASSEMBLY := 1
endif
endif

# Some function for x86_64 are written in FASM, the Flat Assembler, and have
# much better times than the default C code.
ifdef USE_FASM_ASSEMBLY

FASM_SRCS = $(wildcard $(SRC_DIR)/assembly/fasm/*.fasm)
EXCLUDE += $(patsubst %_x86_64.fasm, ! -name "*%.c", $(notdir $(FASM_SRCS)))

# The default is to use assembly code that GCC can understand. LLVM's clang and
# the Portable C Compiler (PCC) are also able to use this, tested on
# Debian GNU/Linux 11, 12, and 13.
else ifneq ($(ASM_ARCH),)

ASM_DIR := $(SRC_DIR)/assembly/$(ASM_ARCH)
ASM_SRCS := $(wildcard $(ASM_DIR)/*.S)
EXCLUDE += $(patsubst %_$(ASM_ARCH).S, ! -name "*%.c", $(notdir $(ASM_SRCS)))

# We need to evaluate the exclude variable immediately since ASM_SRCS is going
# to be modified in the next few steps depending on compiler features and
# whether SIMD_FAST_MATH is enabled.
EXCLUDE := $(EXCLUDE)

# If SIMD clones are being generated, add the relevant assembly files.
ifneq ($(filter $(SIMD_FAST_MATH), ON on TRUE true 1),)

ASM_SRCS += $(wildcard $(ASM_DIR)/simd/*.S)

# C files with inline assembly are only used if SIMD_FAST_MATH mode is not
# enabled. With link-time optimization (LTO) enabled the compiler will always
# select the version of a function found in the .c file, and will ignore the
# SIMD clones. Choosing the .S version prevents this.
else ifneq ($(filter $(NO_INLINE_ASM), OFF off FALSE false 0),)

# If GNU-style inline assembly is supported, and if link-time optimization is
# enabled, then it is better to use the C files found in src/assembly/ instead
# of the plain asm files. Check if inline assembly is supported.
HAVE_GNU_ASM := $(shell $(DET_INLINE_ASM_CMD) && echo yes)

# Remove the corresponding .S files if the .c files are being used instead.
ifeq ($(HAVE_GNU_ASM), yes)
INLINE_ASM_SRCS := $(wildcard $(ASM_DIR)/*.c)
ASM_SRCS := $(filter-out $(INLINE_ASM_SRCS:.c=.S), $(ASM_SRCS))
endif

endif
# End of ifdef SIMD_FAST_MATH.

endif
# End of ifdef USE_FASM_ASSEMBLY.

endif
# End of ifndef NO_ASM.

C_SRCS := $(shell find $(SRC_DIR) $(EXCLUDE) -name "*.c") $(INLINE_ASM_SRCS)
C_OBJS := $(C_SRCS:%=$(BUILD_DIR)/%.o)
ASM_OBJS := $(ASM_SRCS:%=$(BUILD_DIR)/%.o)
FASM_OBJS := $(FASM_SRCS:%=$(BUILD_DIR)/%.o)
OBJS := $(C_OBJS) $(ASM_OBJS) $(FASM_OBJS)

.PHONY: clean install uninstall all help

all: $(TARGET_LIB)

include/tmpl_config.h: config.c $(wildcard config/*.h)
ifeq ($(CC), emcc)
	$(SHELL) emscripten.sh $(CONFIG_FLAGS)
else
	$(CC) $(CONFIG_FLAGS) config.c -o config.out
	./config.out
	rm -f config.out
endif

$(TARGET_LIB_SHARED): $(OBJS) include/tmpl_config.h
	@echo "Building libtmpl.so ..."
	@$(CC) $(OBJS) $(LFLAGS) -o $@

$(TARGET_LIB_STATIC): $(OBJS) include/tmpl_config.h
	@echo "Building libtmpl.a ..."
	@$(AR) rcs $@ $(OBJS)

$(BUILD_DIR)/%.c.o: %.c include/tmpl_config.h
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(CWARN) $< -o $@

$(BUILD_DIR)/%.S.o: %.S include/tmpl_config.h
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(CWARN) $< -o $@

$(BUILD_DIR)/%.fasm.o: %.fasm include/tmpl_config.h
	@mkdir -p $(@D)
	fasm $< $@

clean:
	rm -f config.out *.o
	rm -rf $(BUILD_DIR)
	rm -f include/tmpl_config.h
	rm -f include/tmpl_inttype.h
	rm -f include/tmpl_limits.h
	rm -f include/tmpl_float.h
	rm -f $(TARGET_LIB_SHARED)
	rm -f $(TARGET_LIB_STATIC)

install: $(TARGET_LIB)
	mkdir -p $(prefix)/lib/
	mkdir -p $(prefix)/include/libtmpl/
	cp -r ./include $(prefix)/include/libtmpl/
ifneq ("$(wildcard $(TARGET_LIB_SHARED))", "")
	cp $(TARGET_LIB_SHARED) $(prefix)/lib/$(TARGET_LIB_SHARED)
else
	cp $(TARGET_LIB_STATIC) $(prefix)/lib/$(TARGET_LIB_STATIC)
endif

uninstall:
	rm -rf $(prefix)/include/libtmpl/
	rm -f $(prefix)/lib/$(TARGET_LIB_SHARED)
	rm -f $(prefix)/lib/$(TARGET_LIB_STATIC)

help:
	@echo "\033[0;96mBuild and install libtmpl.\n\nExecutive summary:"
	@echo "\033[0;96m\tTo build and install onto your system:"
	@echo "\033[0;96m\t\tmake -j && sudo make install"
	@echo "\033[0;96m\tTo build and install locally (current user only):"
	@echo "\033[0;96m\t\tmake -j && make install prefix=~/.local\n"
	@echo "\033[0;96mRecognized commands:"
	@echo "\033[0;96m\tmake:"
	@echo "\033[0;96m\t\tCompile the library. Use -j to speed this up."
	@echo "\033[0;96m\tmake install:"
	@echo "\033[0;96m\t\tInstall library into /usr/local/"
	@echo "\033[0;96m\t\t(or into the set prefix)."
	@echo "\033[0;96m\tmake clean:"
	@echo "\033[0;96m\t\tRemove all compiled files in this directory."
	@echo "\033[0;96m\tmake uninstall:"
	@echo "\033[0;96m\t\tRemove all compiled files from this directory and"
	@echo "\033[0;96m\t\tfrom /usr/local/ (or the set prefix)."
	@echo "\033[0;96m\tmake help:"
	@echo "\033[0;96m\t\tPrint this message.\n"
	@echo "\033[0;96mBuild options (see Makefile for more details):"
	@echo "\033[0;96m\tBUILD_SHARED_LIBS:"
	@echo "\033[0;96m\t\tCreate a shared object (libtmpl.so) instead of a"
	@echo "\033[0;96m\t\tstatic library (libtmpl.a)."
	@echo "\033[0;96m\t\tExample: make BUILD_SHARED_LIBS=ON"
	@echo "\033[0;96m\tCC:"
	@echo "\033[0;96m\t\tSet the C compiler."
	@echo "\033[0;96m\t\tExample: make CC=gcc"
	@echo "\033[0;96m\tAR (static builds only):"
	@echo "\033[0;96m\t\tSet the archiver."
	@echo "\033[0;96m\t\tExample: make AR=ar"
	@echo "\033[0;96m\tARCH:"
	@echo "\033[0;96m\t\tChange the output of uname -m."
	@echo "\033[0;96m\t\tExample: make ARCH=i386"
	@echo "\033[0;96m\tDEBUG_BUILD:"
	@echo "\033[0;96m\t\tAdd debug symbols to the build."
	@echo "\033[0;96m\t\tExample: make DEBUG_BUILD=ON"
	@echo "\033[0;96m\tSIMD_FAST_MATH:"
	@echo "\033[0;96m\t\tEnable aggressive math optimizations and compile"
	@echo "\033[0;96m\t\tthe branchless SIMD versions of functions."
	@echo "\033[0;91m\t\tNOTE:"
	@echo "\033[0;91m\t\t\tThe SIMD versions of functions have slightly"
	@echo "\033[0;91m\t\t\tworse errors than their scalar counterparts,"
	@echo "\033[0;91m\t\t\tusually 2-4 ULP instead of 1. With appropriate"
	@echo "\033[0;91m\t\t\thardware this produces a 2-4x boost in speed."
	@echo "\033[0;91m\t\t\tA modern compiler is required for this option"
	@echo "\033[0;91m\t\t\tto be useful (GCC 15+, for example), and the"
	@echo "\033[0;91m\t\t\tOpenMP pragma declare simd must be supported."
	@echo "\033[0;91m\t\tWARNING:"
	@echo "\033[0;91m\t\t\tC23 attributes and / or compiler pragmas are"
	@echo "\033[0;91m\t\t\tused to guard certain functions (like 2Sum)"
	@echo "\033[0;91m\t\t\tfrom the -ffast-math (or equivalent)"
	@echo "\033[0;91m\t\t\toptimization. Such aggressive optimizations are"
	@echo "\033[0;91m\t\t\tneeded to convince GCC to use the SIMD version"
	@echo "\033[0;91m\t\t\tbut may break other functions. Unit tests show"
	@echo "\033[0;91m\t\t\tthat these attribute / pragma guards work as"
	@echo "\033[0;91m\t\t\tintended, but their support is not required by"
	@echo "\033[0;91m\t\t\tthe C standard. If your compiler does not"
	@echo "\033[0;91m\t\t\tsupport the C23 standard, and if it does not"
	@echo "\033[0;91m\t\t\tsupport attributes / pragmas that disable"
	@echo "\033[0;91m\t\t\toptimizations, do not enable SIMD_FAST_MATH."
	@echo "\033[0;96m\t\tExample: make SIMD_FAST_MATH=ON"
	@echo "\033[0;96m\tUSE_OMP:"
	@echo "\033[0;96m\t\tCompile with OpenMP support."
	@echo "\033[0;96m\t\tExample: make USE_OMP=ON"
	@echo "\033[0;96m\tNO_LTO:"
	@echo "\033[0;96m\t\tDisable the -flto flag (link-time optimization)."
	@echo "\033[0;96m\t\tExample: make NO_LTO=ON"
	@echo "\033[0;96m\tNO_MATH:"
	@echo "\033[0;96m\t\tUse the system libm instead of libtmpl's."
	@echo "\033[0;96m\t\tExample: make NO_MATH=ON"
	@echo "\033[0;96m\tNO_LONGLONG:"
	@echo "\033[0;96m\t\tDo not compile any code for long long or"
	@echo "\033[0;96m\t\tunsigned long long."
	@echo "\033[0;96m\t\tExample: make NO_LONGLONG=ON"
	@echo "\033[0;96m\tNO_INLINE:"
	@echo "\033[0;96m\t\tDo not inline any code."
	@echo "\033[0;96m\t\tExample: make NO_INLINE=ON"
	@echo "\033[0;96m\tALWAYS_INLINE:"
	@echo "\033[0;96m\t\tSet the C23 vendor-specific attributes"
	@echo "\033[0;96m\t\t[[gnu::always_inline]] or [[clang::always_inline]]"
	@echo "\033[0;96m\t\tfor inlined functions. Requires C23 support."
	@echo "\033[0;96m\t\tIgnored by compilers that do not support the"
	@echo "\033[0;96m\t\talways_inline attribute."
	@echo "\033[0;96m\t\tExample: make ALWAYS_INLINE=ON"
	@echo "\033[0;96m\tNO_IEEE:"
	@echo "\033[0;96m\t\tDo not probe for IEEE-754 support and instead only"
	@echo "\033[0;96m\t\tonly use portable C code (NOT RECOMMENDED)."
	@echo "\033[0;96m\t\tExample: make NO_IEEE=ON"
	@echo "\033[0;96m\tNO_INT:"
	@echo "\033[0;96m\t\tDo not probe for fixed-width integers and do not"
	@echo "\033[0;96m\t\tattempt any type punning (NOT RECOMMENDED)."
	@echo "\033[0;96m\t\tExample: make NO_INT=ON"
	@echo "\033[0;96m\tNO_ASM:"
	@echo "\033[0;96m\t\tDo not use any assembly code."
	@echo "\033[0;96m\t\tExample: make NO_ASM=ON"
	@echo "\033[0;91m\t\tNOTE:"
	@echo "\033[0;91m\t\t\tThis is NOT recommended on most architectures"
	@echo "\033[0;91m\t\t\tsince the assembly code outperforms the C code."
	@echo "\033[0;91m\t\t\tSome architectures require this to be set."
	@echo "\033[0;91m\t\t\tIf you are on armv7l and lack floating point"
	@echo "\033[0;91m\t\t\thardware support, you MUST set NO_ASM=ON."
	@echo "\033[0;91m\t\t\tThis is because the Makefile assumes armv7l"
	@echo "\033[0;91m\t\t\tmachines will have hardware floats, even"
	@echo "\033[0;91m\t\t\tthough this is not required."
	@echo "\033[0;96m\tNO_INLINE_ASM:"
	@echo "\033[0;96m\t\tUse the .S files in src/assembly/ instead of the"
	@echo "\033[0;96m\t\tC files written with GNU inline assembly. This is"
	@echo "\033[0;96m\t\talways the case if SIMD_FAST_MATH is set."
	@echo "\033[0;96m\t\tExample: make NO_INLINE_ASM=ON"
	@echo "\033[0;96m\tUSE_FASM (x86_64 / amd64 only):"
	@echo "\033[0;96m\t\tUse Flat Assembly (FASM) code instead of"
	@echo "\033[0;96m\t\tGNU Assembly (GAS). Requires fasm to be installed."
	@echo "\033[0;96m\t\tExample: make USE_FASM=ON"
	@echo "\033[0;96m\tUSE_MEMCPY:"
	@echo "\033[0;96m\t\tUse memcpy for copying data instead of for-loops."
	@echo "\033[0;96m\t\tExample: make USE_MEMCPY=ON"
	@echo "\033[0;96m\tUSE_VOLATILE:"
	@echo "\033[0;96m\t\tMake the macro TMPL_VOLATILE expand to 'volatile'"
	@echo "\033[0;96m\t\tinstead of nothing. Certain functions like 2Sum"
	@echo "\033[0;96m\t\tand routines implementing double-double arithmetic"
	@echo "\033[0;96m\t\tmay need this to protect against compiler"
	@echo "\033[0;96m\t\toptimizations. This is not required by compilers"
	@echo "\033[0;96m\t\tthat respect the C standards requirements for"
	@echo "\033[0;96m\t\tfloating-point arithmetic (GCC, Clang, MSVC), but"
	@echo "\033[0;96m\t\tit is necessary on other compilers (ICC)."
	@echo "\033[0;96m\t\tExample: make USE_VOLATILE=ON"
	@echo "\033[0;96m\tEXTRA_FLAGS:"
	@echo "\033[0;96m\t\tAdd extra flags for the C compiler."
	@echo "\033[0;96m\t\tExample: make EXTRA_FLAGS=\"-Wno-float-equal\""
