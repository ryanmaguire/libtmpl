cmake_minimum_required(VERSION 3.20)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
include(ParseCStandard)

option(OMP "User OpenMP, if available" TRUE)
option(NO_INLINE "" TRUE)
option(NO_MATH "" TRUE)
option(NO_IEEE "" TRUE)
option(NO_ASM "" TRUE)
option(NO_BUILTIN "" TRUE)
option(FASM "" TRUE)
option(BUILD_TESTS "" FALSE)
option(NO_LONGLONG "" FALSE)
option(NO_INT "" FALSE)

if(NOT DEFINED STDVER)
    set(STDVER "-std=c89" CACHE STRING "" FORCE)
endif()

project(libtmpl_library LANGUAGES C)

cmake_path(GET CMAKE_SOURCE_DIR PARENT_PATH TMPL_PARENT_DIR)

add_library(tmpl SHARED)
target_include_directories(tmpl PUBLIC "include" "${TMPL_PARENT_DIR}")

# Build config.c and run to generate "include/tmpl_config.h"
add_executable(tmpl_config config.c)
add_custom_command(
    OUTPUT "include/tmpl_config.h" "include/tmpl_inttype.h"
    DEPENDS tmpl_config
    BYPRODUCTS "include/tmpl_config.h" "include/tmpl_inttype.h"
    COMMAND "$<TARGET_FILE:tmpl_config>"
    COMMAND
        ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/include/tmpl_config.h
        include
    COMMAND
        ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/include/tmpl_inttype.h
        include
    VERBATIM
)

# Declare a dependency on the generated tmpl_config.h file to ensure that we wait for its generate before building the
# tmpl target
target_sources(tmpl PRIVATE "include/tmpl_config.h" "include/tmpl_inttype.h")

set_c_standard(tmpl "${STDVER}")

if(NO_LONGLONG)
    target_compile_definitions(tmpl_config PUBLIC TMPL_SET_LONGLONG_FALSE)
endif()

if(OMP)
    # Build with OpenMP, if it is supported by the toolchain
    find_package(OpenMP)
    if(OpenMP_C_FOUND)
        message(STATUS "OpenMP ${OpenMP_C_VERSION} found")
        target_link_libraries(tmpl PUBLIC OpenMP::OpenMP_C)
    else()
        message(
            WARNING
            "OpenMP was requested, but OpenMP support was not detected for this compiler: \
            ${CMAKE_C_COMPILER_ID} ${CMAKE_C_COMPILER_VERSION}"
        )
    endif()
endif()

if(NOT NO_INLINE)
    if(STDVER STREQUAL "-std=c89")
        message(
            FATAL_ERROR
            "Error: inline mode cannot be used with C89.\n        Set -std to a version supporting inline."
        )
    endif()

    if(STDVER STREQUAL "-std=c90")
        message(
            FATAL_ERROR
            "Error: inline mode cannot be used with C90.\n        Set -std to a version supporting inline."
        )
    endif()
endif()

if(NO_MATH)
    # Do not use libtmpl's libm implementation

    # TODO what to do for other systems?
    if(UNIX)
        target_link_libraries(tmpl PRIVATE m)
    endif()
    # TODO: set up file exclusions
else()
    target_compile_definitions(tmpl_config PUBLIC TMPL_SET_USE_MATH_TRUE)
endif()

if(NOT NO_INLINE)
    target_compile_definitions(tmpl_config PUBLIC TMPL_SET_INLINE_TRUE)
endif()

if(NO_IEEE)
    target_compile_definitions(tmpl_config PUBLIC TMPL_SET_TMPL_USE_IEEE_FALSE)
endif()

if(NO_INT)
    target_compile_definitions(tmpl_config PUBLIC TMPL_SET_NO_INT)
endif()

add_subdirectory("src")

# TODO: set up ASM support
string(TOLOWER "${CMAKE_SYSTEM_PROCESSOR}" system_processor)
set(X86_64_ARCHES "amd64;x86_64")
set(ARM64_ARCHES "aarch64;arm64")
set(ARMHF_ARCHES "armv7l;")
if(NOT NO_ASM)
    if(system_processor IN_LIST X86_64_ARCHES)
        enable_language(ASM)

        if(NOT NO_BUILTIN)
            # This includes Windows AMD64 and Unix x86_64
            add_subdirectory("src/builtins/x86_64")

            #TODO set up C file exclusion of
            #BUILTIN_EXCLUDE := \
            #-not -name "tmpl_cos_double.c" -and \
            #-not -name "tmpl_cos_float.c" -and \
            #-not -name "tmpl_cos_ldouble.c" -and \
            #-not -name "tmpl_sin_double.c" -and \
            #-not -name "tmpl_sin_float.c" -and \
            #-not -name "tmpl_sin_ldouble.c" -and \
            #-not -name "tmpl_sincos_double.c" -and \
            #-not -name "tmpl_sincos_float.c" -and \
            #-not -name "tmpl_sincos_ldouble.c" -and
        endif()

        if(FASM)
            add_subdirectory("src/assembly/fasm")
            #TODO exclude
            # ASM_EXCLUDE := \
            # -not -name "tmpl_sqrt_double.c" -and \
            # -not -name "tmpl_sqrt_float.c" -and

            # TODO add checks for fasm compatibility
        elseif()
            add_subdirectory("src/assembly/x86_64")
            #TODO exclude
            # ASM_EXCLUDE := \
            # -not -name "tmpl_trailing_zeros_char.c" -and \
            # -not -name "tmpl_trailing_zeros_int.c" -and \
            # -not -name "tmpl_trailing_zeros_long.c" -and \
            # -not -name "tmpl_trailing_zeros_short.c" -and \
            # -not -name "tmpl_trailing_zeros_uint.c" -and \
            # -not -name "tmpl_trailing_zeros_uchar.c" -and \
            # -not -name "tmpl_trailing_zeros_ulong.c" -and \
            # -not -name "tmpl_trailing_zeros_ushort.c" -and \
            # -not -name "tmpl_sqrt_double.c" -and \
            # -not -name "tmpl_sqrt_float.c" -and \
            # -not -name "tmpl_sqrt_ldouble.c" -and \
            # -not -name "tmpl_floor_double.c" -and \
            # -not -name "tmpl_floor_float.c" -and \
            # -not -name "tmpl_floor_ldouble.c" -and
        endif()
    elseif(system_processor in ARM64_ARCHES)
        enable_language(ASM)
        if(NOT NO_BUILTIN)
            add_subdirectory("src/builtins/aarch64")
            # TODO exclude
            # BUILTIN_EXCLUDE := \
            # -not -name "tmpl_cos_double.c" -and \
            # -not -name "tmpl_cos_float.c" -and \
            # -not -name "tmpl_cos_ldouble.c" -and \
            # -not -name "tmpl_floor_ldouble.c" -and \
            # -not -name "tmpl_sin_double.c" -and \
            # -not -name "tmpl_sin_float.c" -and \
            # -not -name "tmpl_sin_ldouble.c" -and \
            # -not -name "tmpl_sincos_double.c" -and \
            # -not -name "tmpl_sincos_float.c" -and \
            # -not -name "tmpl_sincos_ldouble.c" -and \
            # -not -name "tmpl_sqrt_ldouble.c" -and
        endif()

        add_subdirectory("src/assembly/aarch64")

        #TODO exclude
        # ASM_EXCLUDE := \
        # -not -name "tmpl_floor_double.c" -and \
        # -not -name "tmpl_floor_float.c" -and \
        # -not -name "tmpl_sqrt_double.c" -and \
        # -not -name "tmpl_sqrt_float.c" -and \
    elseif(system_processor IN ARMHF_ARCHES)
        enable_language(ASM)
        add_subdirectory("src/assembly/armv7l")

        #TODO exclude
        # ASM_EXCLUDE :=
        # -not -name "tmpl_sqrt_double.c" -and \
        # -not -name "tmpl_sqrt_float.c" -and \
        # -not -name "tmpl_sqrt_ldouble.c" -and
    endif()
endif()

if(BUILD_TESTS)
    add_subdirectory("tests")
endif()

add_library(tmpl::tmpl ALIAS tmpl)

include(GNUInstallDirs)
install(
    TARGETS tmpl
    RUNTIME
    DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}}
)
