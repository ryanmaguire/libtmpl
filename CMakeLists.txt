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
#   Date:       January 23, 2026                                               #
################################################################################
cmake_minimum_required(VERSION 3.14)

# libtmpl is written entirely in C and some assembly.
project(libtmpl C ASM)

# Choose release mode by default if the user does not specify a build type.
get_property(TMPL_MULTI_CONFIG GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
if (NOT TMPL_MULTI_CONFIG AND NOT CMAKE_BUILD_TYPE)
    set(
        CMAKE_BUILD_TYPE Release CACHE STRING
        "Build type: Debug, Release, RelWithDebInfo, or MinSizeRel" FORCE
    )
endif()

# Default build options for libtmpl.
option(BUILD_SHARED_LIBS "Build shared library" OFF)

# OpenMP support, useful for parallel processing. Disabled by default
# since OpenMP is not a required dependency for libtmpl.
option(OMP "Enable OpenMP support" OFF)

# Whether or not to use libtmpl's implementation of libm, or the one that
# comes with your C compiler. If you disable this, then your compiler must
# support the C99 standard (or higher). The original C89 standard lacks many
# useful math functions that libtmpl requires (and implements).
option(NO_MATH "Do not use libtmpl's implementation of libm" OFF)

# Whether or not to compile long long functions. On some platforms, like
# 64-bit GNU/Linux, long and long long are the same type, so compiling the
# long long versions is redundant.
option(NO_LONGLONG "Do not build long long functions" OFF)

# Whether small functions should be inlined. If you want the symbols for
# all libtmpl functions available in the generated library file, then you
# should enable this. This is useful if you are using something like the
# D programming languages interface to C functions. But note, benchmarks
# show that inlining small functions produces a significant speed boost
# (2x in some cases).
option(NO_INLINE "Disable inlining" OFF)

# Enable the C23 attributes [[gnu::always_inline]] or [[clang::always_inline]]
# for inlined functions. Your compiler must support C23 attributes for this.
option(ALWAYS_INLINE "Force always_inline attributes (requires C23)" OFF)

# Do not use type punning for any functions. Most compilers support
# type punning, disabling this can produce a serious performance hit
# (10x or worse in some cases).
option(NO_IEEE "Disable IEEE-754 optimization (use portable code)" OFF)

# Do not attempt to use fixed-width integers. Enabling this may
# harm performance.
option(NO_INT "Disable fixed-width integer probing" OFF)

# Do not use any assembly code, C code only. Not recommended, this file will
# detect your architecture and select the correct assembly code if possible,
# and fall back to C code if the architecture is not supported. Many of the
# assembly functions are significantly faster than their C counterparts.
option(NO_ASM "Disable all assembly code" OFF)

# Use the Flat Assembly (FASM) instead of the GNU Assembly language (GAS).
# Benchmarks show FASM is just as fast as GAS, it is worth experiment with.
option(FASM "Use FASM instead of GAS (Requires fasm installed)" OFF)

# Use the standard library function memcpy instead of for-loops.
option(USE_MEMCPY "Use memcpy instead of for-loops" OFF)

# Set the TMPL_VOLATILE macro to "volatile" instead of being empty. This may
# be necessary for libtmpl's double-double arithmetic routines if your compiler
# does not implement the C23 [[gnu::optimize(...)]] attribute.
option(USE_VOLATILE "Set the TMPL_VOLATILE macro to volatile" OFF)

# Options for carefully and correctly performing the double-double split.
option(VOLATILE_SPLIT "Force volatile keyword for double splitting" OFF)
option(CAUTIOUS_SPLIT "Force cautious (multi-volatile) double splitting" OFF)
option(NO_VOLATILE_SPLIT "Disable volatile splitting (Not Recommended)" OFF)

# Enable very aggressive optimizations and use OpenMP to create SIMD versions of
# several of libtmpl's functions. Only supported by a few compilers (GCC 15+).
# It enables -ffast-math, -march=native, and -fopenmp-simd, and requires C23
# attributes to protect functions like 2Sum and 2Prod from these optimizations.
# With appropriate hardware this can double the speed of some functions, at the
# cost of slightly larger error (roughly 1-4 ULP instead of 1-2 ULP).
option(SIMD_FAST_MATH "Enable aggressive SIMD fast-math vectorization" OFF)

# Disable the -flto flag (link-time optimization). Some compilers do not support
# it. NVIDIA's nvc is detected automatically by check_ipo_supported() below.
option(NO_LTO "Disable link-time optimization (-flto)" OFF)

# Manually override the detected architecture. The Makefile uses uname -m, CMake
# uses CMAKE_SYSTEM_PROCESSOR. When emulating (e.g. running i386 binaries on an
# x86_64 host) the detected value may be wrong Set this to pick the correct
# assembly code. This has no effect when NO_ASM is enabled.
set(ARCH "" CACHE STRING "Override detected architecture (e.g. i386)")

# Any extra flags to pass to the C compiler.
set(EXTRA_FLAGS "" CACHE STRING "Extra flags passed to the C compiler")

# Detect the architecture. Honor the manual ARCH override if given, otherwise
# fall back to what CMake probed for the target processor.
if (ARCH)
    string(TOLOWER "${ARCH}" TMPL_ARCH)
else()
    string(TOLOWER "${CMAKE_SYSTEM_PROCESSOR}" TMPL_ARCH)
endif()

if(TMPL_ARCH MATCHES "amd64|x86_64")
    set(TMPL_ARCH "x86_64")
elseif(TMPL_ARCH MATCHES "i386|x86")
    set(TMPL_ARCH "i386")
elseif(TMPL_ARCH MATCHES "aarch64|arm64")
    set(TMPL_ARCH "aarch64")
elseif(TMPL_ARCH MATCHES "armv7.*")
    set(TMPL_ARCH "armv7l")
elseif(TMPL_ARCH MATCHES "ppc64le")
    set(TMPL_ARCH "ppc64le")
endif()

message(STATUS "libtmpl detected architecture: ${TMPL_ARCH}")

# Grab all of the C sources.
file(GLOB_RECURSE SOURCES "src/*.c")

set(CONFIG_FLAGS "")

# Several architectures require the volatile keyword for the double split
# to be performed correctly. Check for these architectures.
set (NEEDS_VOLATILE_SPLIT FALSE)
if (TMPL_ARCH MATCHES "aarch64|arm64|armv7l|ppc|ppc64|ppc64le|riscv64")
    set(NEEDS_VOLATILE_SPLIT TRUE)
endif()

# Check if we need to enable volatile flags.
if (NOT NO_VOLATILE_SPLIT)

    # i386 needs several volatile flags (one for each arithmetic step).
    if (CAUTIOUS_SPLIT OR (TMPL_ARCH STREQUAL "i386"))
        list(APPEND CONFIG_FLAGS TMPL_USE_CAUTIOUS_DOUBLE_SPLIT)

    # The other architectures only need one.
    elseif (VOLATILE_SPLIT OR NEEDS_VOLATILE_SPLIT)
        list(APPEND CONFIG_FLAGS TMPL_USE_VOLATILE_DOUBLE_SPLIT)
    endif()
endif()

# Remove libm files if the user does not want libtmpl's implementation.
if (NO_MATH)
    list(FILTER SOURCES EXCLUDE REGEX ".*_math_.*\\.c$")

# Otherwise, add USE_MATH to the config flags.
else()
    list(APPEND CONFIG_FLAGS TMPL_SET_USE_MATH_TRUE)
endif()

# If inline support is available, remove the non-inline versions.
if (NOT NO_INLINE)
    list(APPEND CONFIG_FLAGS TMPL_SET_INLINE_TRUE)
    list(FILTER SOURCES EXCLUDE REGEX ".*_no_inline_.*\\.c$")
endif()

# Users may wish to force inlining functions. config.c only does this if the
# corresponding macro is set.
if (ALWAYS_INLINE)
    list(APPEND CONFIG_FLAGS TMPL_SET_ALWAYS_INLINE_TRUE)
endif()

# Remove long long files if long long support is not requested or available.
if (NO_LONGLONG)
    list(APPEND CONFIG_FLAGS TMPL_SET_LONGLONG_FALSE)
    list(FILTER SOURCES EXCLUDE REGEX ".*llong\\.c$")
endif()

# Disable IEEE-754 type-punning if requested (not recommended).
if (NO_IEEE)
    list(APPEND CONFIG_FLAGS TMPL_SET_TMPL_USE_IEEE_FALSE)
endif()

# Disable use of memcpy if requested.
if (USE_MEMCPY)
    list(APPEND CONFIG_FLAGS TMPL_SET_USE_MEMCPY_TRUE)
endif()

# Disable fixed-width integers if not requested (not recommended).
if (NO_INT)
    list(APPEND CONFIG_FLAGS TMPL_SET_NO_INT)
endif()

# Option to set the volatile keyword for certain functions.
if (USE_VOLATILE)
    list(APPEND CONFIG_FLAGS TMPL_USE_VOLATILE)
endif()

# Set the SIMD fast-math config macro. The matching compile and link flags
# (-ffast-math, -march=native, -fopenmp-simd, -std=c23) are added later in the
# compiler-flags section, since they belong to the targets, not to config.c.
if (SIMD_FAST_MATH)
    list(APPEND CONFIG_FLAGS TMPL_SET_USE_SIMD_FAST_MATH_TRUE)
endif()

# The files tmpl_config.h, tmpl_float.h, and more, are all created by the
# config.c file which probes the compiler and runs before the main build.
add_executable(tmpl_config_generate config.c)

# Add the config flags for config.c.
target_compile_definitions(tmpl_config_generate PRIVATE ${CONFIG_FLAGS})

add_custom_command(
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/include/tmpl_config.h
    COMMAND tmpl_config_generate
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    DEPENDS tmpl_config_generate
    COMMENT "Generating tmpl_config.h with flags: ${CONFIG_FLAGS}"
)

add_custom_target(
    generate_config DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/include/tmpl_config.h
)

# Add the assembly sources next.
set(ASM_SOURCES "")

# Assembly code is enabled by default.
if (NOT NO_ASM)

    # Check if MSVC (Visual Studio) is used.
    # MSVC cannot compile GAS (.S) files directly.
    if (MSVC)
        enable_language(ASM_MASM)

        file(GLOB ASM_SOURCES "src/assembly/x86_64_msvc/*.i")

        # Exclude corresponding C files.
        foreach(f ${ASM_SOURCES})
            get_filename_component(fname ${f} NAME_WE)
            string(REPLACE "_x86_64_msvc" "" pure_name ${fname})
            list(FILTER SOURCES EXCLUDE REGEX ".*${pure_name}\\.c$")
        endforeach()

        set_source_files_properties(${ASM_SOURCES} PROPERTIES LANGUAGE ASM_MASM)
    else()
        if (FASM)
            find_program(FASM_EXECUTABLE fasm)

            if (NOT FASM_EXECUTABLE)
                message(
                    FATAL_ERROR
                    "FASM enabled but 'fasm' executable not found."
                )
            else()
                message(STATUS "Using FASM for x86-64 assembly code.")
            endif()

            # Location of all of the FASM file.
            file(GLOB ASM_FILES "src/assembly/fasm/*.fasm")

            foreach(f ${ASM_FILES})
                get_filename_component(fname ${f} NAME_WE)
                set(f_out "${CMAKE_CURRENT_BINARY_DIR}/${fname}.o")

                add_custom_command(
                    OUTPUT ${f_out}
                    COMMAND ${FASM_EXECUTABLE} ${f} ${f_out} > fasm.log
                    DEPENDS ${f}
                    COMMENT "Building ASM object ${f}"
                    COMMAND rm -f fasm.log
                )

                list(APPEND ASM_SOURCES ${f_out})
            endforeach()
        else()
            file(GLOB ASM_SOURCES "src/assembly/${TMPL_ARCH}/*.S")
        endif()

        # Exclude corresponding C files.
        foreach(f ${ASM_SOURCES})
            get_filename_component(fname ${f} NAME_WE)
            string(REPLACE "_${TMPL_ARCH}" "" pure_name ${fname})
            list(FILTER SOURCES EXCLUDE REGEX ".*${pure_name}\\.c$")
        endforeach()
    endif()

    # Remove the assembly libm files if libtmpl's algorithms are not requested.
    if (NO_MATH)
        list(FILTER ASM_SOURCES EXCLUDE REGEX "_math_")
    endif()
endif()

# Needed to get libtmpl to compile when using MinGW or MSYS2 on Windows.
if (MINGW OR MSYS)
    set(CMAKE_C_USE_RESPONSE_FILE_FOR_OBJECTS 1)
    set(CMAKE_ASM_USE_RESPONSE_FILE_FOR_OBJECTS 1)
    set(CMAKE_C_RESPONSE_FILE_LINK_FLAG "@")
    message(STATUS "Building in MinGW / MSYS environment.")
endif()

# Add sources for libtmpl (C and assembly).
add_library(tmpl ${SOURCES} ${ASM_SOURCES})

# Ensure config is generated before building library
add_dependencies(tmpl generate_config)

# Add libtmpl to the include path.
target_include_directories(
    tmpl PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
)

# Check for OMP support.
if (OMP)
    find_package(OpenMP)
    if (OpenMP_C_FOUND)
        message(STATUS "libtmpl compiling with OpenMP support.")
    else()
        message(WARNING "OpenMP support requested but not found.")
    endif()
endif()

# Add compiler and linker flags.
if (NOT MSVC)

    # GCC and Clang support -march=native. Since binaries of libtmpl are
    # not provided (the user compiles from source), it is beneficial to
    # enable this flag. It provides a speed boost in many applications
    # (rss_ringoccs can see up to 23% speed boosts simply by enabling).
    include(CheckCCompilerFlag)
    check_c_compiler_flag("-march=native" COMPILER_SUPPORTS_MARCH_NATIVE)

    # Default flags for building libtmpl.
    target_compile_options(tmpl PRIVATE -Wall -Wextra -Wpedantic -fPIC)

    # Check if we can enable -march=native.
    if(COMPILER_SUPPORTS_MARCH_NATIVE)
        target_compile_options(tmpl PRIVATE -march=native)
    endif()

    # If libtmpl's implementation of libm is not used, we need to link to libm.
    if (NO_MATH)
        target_link_libraries(tmpl PRIVATE m)
    endif()

    # Add OMP flags if necessary.
    if (OpenMP_C_FOUND)

        target_compile_options(
            tmpl PRIVATE
            $<$<C_COMPILER_ID:AppleClang>:-Xpreprocessor>
            -fopenmp
        )

        target_link_libraries(tmpl PRIVATE OpenMP::OpenMP_C)
    endif()
else()

    # Flags for MSVC on Windows. Warning C4146 complains about negating
    # unsigned ints. This is valid well-defined behavior in C, it is
    # equivalent to computing 2^N - n where N is the number of bits in n.
    # Turn this warning off when using MSVC.
    target_compile_options(
        tmpl PRIVATE $<$<COMPILE_LANGUAGE:C>:/W4 /wd4146>
    )

    if (OpenMP_C_FOUND)
        target_compile_options(tmpl PRIVATE $<$<COMPILE_LANGUAGE:C>:/openmp>)
        target_link_libraries(tmpl PRIVATE OpenMP::OpenMP_C)
    endif()
endif()

# SIMD_FAST_MATH: aggressive fast-math vectorization (GCC 15+, clang 22+).
if (SIMD_FAST_MATH)
    include(CheckCCompilerFlag)

    # Apply a compile (and link) flag only if the active compiler accepts it.
    # check_c_compiler_flag compiles a probe, so it is both compiler and
    # architecture aware.
    function(tmpl_add_supported_flag tgt flag)
        string(MAKE_C_IDENTIFIER "TMPL_CC_HAS_${flag}" probe)
        check_c_compiler_flag("${flag}" ${probe})
        if (${probe})
            target_compile_options(${tgt} PRIVATE "${flag}")
            target_link_options(${tgt} PRIVATE "${flag}")
        endif()
    endfunction()

    # SIMD_FAST_MATH mode requires C23 attributes and modern compiler features.
    set_target_properties(
        tmpl tmpl_config_generate PROPERTIES
        C_STANDARD 23
        C_STANDARD_REQUIRED ON
    )

    if (MSVC)

        # MSVC equivalent of -ffast-math and -fopenmp-simd.
        target_compile_options(tmpl PRIVATE /fp:fast /openmp:experimental)
    else()

        # Fast math.
        tmpl_add_supported_flag(tmpl -ffast-math)

        # Tune for the build machine. GCC uses use -march=native for some
        # architectures and -mcpu=native for others.
        check_c_compiler_flag("-march=native" TMPL_CC_HAS_MARCH_NATIVE)

        if (TMPL_CC_HAS_MARCH_NATIVE)
            target_compile_options(tmpl PRIVATE -march=native)
            target_link_options(tmpl PRIVATE -march=native)
        else()
            tmpl_add_supported_flag(tmpl -mcpu=native)
        endif()

        # OpenMP SIMD vectorizer only, the full OpemMP runtime is not needed.
        tmpl_add_supported_flag(tmpl -fopenmp-simd)
    endif()
endif()

# Extra user-supplied compiler flags.
if (EXTRA_FLAGS)
    separate_arguments(EXTRA_FLAGS_LIST NATIVE_COMMAND "${EXTRA_FLAGS}")
    target_compile_options(tmpl PRIVATE ${EXTRA_FLAGS_LIST})
    target_compile_options(tmpl_config_generate PRIVATE ${EXTRA_FLAGS_LIST})
endif()

# Check for support for link-time optimization.
include(CheckIPOSupported)
check_ipo_supported(RESULT result)

# Add LTO if possible.
if (result AND NOT NO_LTO)
    message(STATUS "libtmpl compiling with LTO enabled.")
    set_property(TARGET tmpl PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
    set_property(TARGET tmpl PROPERTY INTERPROCEDURAL_OPTIMIZATION_DEBUG FALSE)
endif()

# Install binary files (.so, .lib, .dll, or .a).
install(
    TARGETS tmpl
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

# Install header files.
install(DIRECTORY include/ DESTINATION include/libtmpl/include)
