cmake_minimum_required(VERSION 3.23)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
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
option(ENABLE_VERBOSE "" FALSE)

if(NOT DEFINED STDVER)
    set(STDVER "-std=c89" CACHE STRING "" FORCE)
endif()

project(libtmpl LANGUAGES C)

cmake_path(GET CMAKE_CURRENT_SOURCE_DIR PARENT_PATH TMPL_PARENT_DIR)

add_library(tmpl SHARED)

target_include_directories(
    tmpl
    PUBLIC
        "$<INSTALL_INTERFACE:include>"
        "$<BUILD_INTERFACE:${TMPL_PARENT_DIR}>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>"
)
set_target_properties(tmpl PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
if(MSVC)
    target_compile_options(tmpl PRIVATE /MP)
endif()

# Build config.c and run to generate "include/tmpl_config.h"
add_executable(tmpl_config config.c)
add_custom_command(
    OUTPUT "include/tmpl_config.h" "include/tmpl_inttype.h"
    DEPENDS tmpl_config
    COMMAND "$<TARGET_FILE:tmpl_config>"
    COMMAND
        ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_BINARY_DIR}/include/tmpl_config.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    COMMAND
        ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_BINARY_DIR}/include/tmpl_inttype.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    VERBATIM
)

target_sources(
    tmpl
    PUBLIC
        FILE_SET HEADERS
        BASE_DIRS
            ${CMAKE_CURRENT_SOURCE_DIR}/include
            ${CMAKE_CURRENT_BINARY_DIR}/include
)
add_subdirectory("include")

set_c_standard(TARGET tmpl
    STDVER "${STDVER}"
    ENABLE_VERBOSE ${ENABLE_VERBOSE}
)

include(CheckIPOSupported)
# Optional IPO. Do not use IPO if it's not supported by compiler.
check_ipo_supported(RESULT IPO_SUPPORTED OUTPUT IPO_CHECK_OUTPUT)
if(IPO_SUPPORTED)
    message(
        STATUS
        "Interprocedural Optimization/Link-Time Optimization is supported."
    )
else()
    message(
        WARNING
        "Interprocedural Optimization/Link-Time Optimization is not supported: ${IPO_CHECK_OUTPUT}"
    )
endif()

if(NO_LONGLONG)
    target_compile_definitions(tmpl_config PUBLIC TMPL_SET_LONGLONG_FALSE)
    list(APPEND SOURCE_EXCLUSION_LIST "tmpl_abs_llong.c")
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

    list(
        APPEND
        SOURCE_EXCLUSION_LIST
        "tmpl_abs_double.c"
        "tmpl_abs_float.c"
        "tmpl_abs_ldouble.c"
        "tmpl_arctan2_double.c"
        "tmpl_arctan2_float.c"
        "tmpl_arctan2_ldouble.c"
        "tmpl_arctan_double.c"
        "tmpl_arctan_float.c"
        "tmpl_arctan_ldouble.c"
        "tmpl_cos_double.c"
        "tmpl_floor_double.c"
        "tmpl_floor_float.c"
        "tmpl_sin_double.c"
    )
else()
    target_compile_definitions(tmpl_config PUBLIC TMPL_SET_USE_MATH_TRUE)
endif()

if(NOT NO_INLINE)
    target_compile_definitions(tmpl_config PUBLIC TMPL_SET_INLINE_TRUE)

    list(
        APPEND
        SOURCE_EXCLUSION_LIST
        "tmpl_abs_char.c"
        "tmpl_abs_short.c"
        "tmpl_abs_int.c"
        "tmpl_abs_long.c"
        "tmpl_abs_llong.c"
        "tmpl_abs_double.c"
        "tmpl_abs_float.c"
        "tmpl_abs_ldouble.c"
        "tmpl_arctan_asymptotic_double.c"
        "tmpl_arctan_asymptotic_float.c"
        "tmpl_arctan_asymptotic_ldouble.c"
        "tmpl_arctan_maclaurin_double.c"
        "tmpl_arctan_maclaurin_float.c"
        "tmpl_arctan_maclaurin_ldouble.c"
        "tmpl_arctan_pade_double.c"
        "tmpl_arctan_pade_float.c"
        "tmpl_arctan_pade_ldouble.c"
        "tmpl_arctan_very_small_double.c"
        "tmpl_arctan_very_small_float.c"
        "tmpl_arctan_very_small_ldouble.c"
        "tmpl_cbrt_pade_double.c"
        "tmpl_cbrt_pade_float.c"
        "tmpl_cbrt_pade_ldouble.c"
        "tmpl_cbrt_taylor_double.c"
        "tmpl_cbrt_taylor_float.c"
        "tmpl_cbrt_taylor_ldouble.c"
        "tmpl_complex_abs_double.c"
        "tmpl_complex_abs_float.c"
        "tmpl_complex_abs_ldouble.c"
        "tmpl_complex_abs_squared.c"
        "tmpl_complex_add.c"
        "tmpl_complex_addto.c"
        "tmpl_complex_quick_abs.c"
        "tmpl_copysign_float.c"
        "tmpl_copysign_double.c"
        "tmpl_copysign_ldouble.c"
        "tmpl_sin_pade_double.c"
        "tmpl_sin_pade_float.c" # FIXME: "tmpl_sin_pade_float.c" not found
        "tmpl_sin_pade_ldouble.c" # FiXME: tmpl_sin_pade_ldouble.c not found
        "tmpl_sin_pade_pi_double.c"
        "tmpl_sin_pade_pi_float.c" # FIXME: tmpl_sin_pade_pi_float.c not found
        "tmpl_sin_pade_pi_ldouble.c" # FIXME: tmpl_sin_pade_pi_ldouble.c not found
        "tmpl_sin_very_small_double.c"
    )
endif()

if(NO_IEEE)
    target_compile_definitions(tmpl_config PUBLIC TMPL_SET_TMPL_USE_IEEE_FALSE)
endif()

if(NO_INT)
    target_compile_definitions(tmpl_config PUBLIC TMPL_SET_NO_INT)
endif()

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

            list(
                APPEND
                SOURCE_EXCLUSION_LIST
                "tmpl_cos_double.c"
                "tmpl_cos_float.c"
                "tmpl_cos_ldouble.c"
                "tmpl_sin_double.c"
                "tmpl_sin_float.c"
                "tmpl_sin_ldouble.c"
                "tmpl_sincos_double.c"
                "tmpl_sincos_float.c"
                "tmpl_sincos_ldouble.c"
            )
        endif()

        if(FASM)
            add_subdirectory("src/assembly/fasm")
            list(
                APPEND
                SOURCE_EXCLUSION_LIST
                "tmpl_sqrt_double.c"
                "tmpl_sqrt_float.c"
            )

            # TODO add checks for fasm compatibility
        elseif()
            add_subdirectory("src/assembly/x86_64")
            list(
                APPEND
                SOURCE_EXCLUSION_LIST
                "tmpl_trailing_zeros_char.c"
                "tmpl_trailing_zeros_int.c"
                "tmpl_trailing_zeros_long.c"
                "tmpl_trailing_zeros_short.c"
                "tmpl_trailing_zeros_uint.c"
                "tmpl_trailing_zeros_uchar.c"
                "tmpl_trailing_zeros_ulong.c"
                "tmpl_trailing_zeros_ushort.c"
                "tmpl_sqrt_double.c"
                "tmpl_sqrt_float.c"
                "tmpl_sqrt_ldouble.c"
                "tmpl_floor_double.c"
                "tmpl_floor_float.c"
                "tmpl_floor_ldouble.c"
            )
        endif()
    elseif(system_processor IN_LIST ARM64_ARCHES)
        enable_language(ASM)

        if(NOT NO_BUILTIN)
            set(ARM64_USE_BUILTIN TRUE)
            add_subdirectory("src/builtins/aarch64")
            list(
                APPEND
                SOURCE_EXCLUSION_LIST
                "tmpl_cos_double.c"
                "tmpl_cos_float.c"
                "tmpl_cos_ldouble.c"
                "tmpl_floor_ldouble.c"
                "tmpl_sin_double.c"
                "tmpl_sin_float.c"
                "tmpl_sin_ldouble.c"
                "tmpl_sincos_double.c" #FIXME file not found
                "tmpl_sincos_float.c" #FIXME file not found
                "tmpl_sincos_ldouble.c" #FIXME file not found
                "tmpl_sqrt_ldouble.c"
            )
        endif()

        add_subdirectory("src/assembly/aarch64")
    elseif(system_processor IN_LIST ARMHF_ARCHES)
        enable_language(ASM)

        add_subdirectory("src/assembly/armv7l")
        list(
            APPEND
            SOURCE_EXCLUSION_LIST
            "tmpl_sqrt_double.c"
            "tmpl_sqrt_float.c"
            "tmpl_sqrt_ldouble.c"
        )
    endif()
endif()

list(LENGTH SOURCE_EXCLUSION_LIST SOURCE_EXCLUSION_LIST_SIZE)
if(SOURCE_EXCLUSION_LIST_SIZE GREATER 1)
    list(REMOVE_DUPLICATES SOURCE_EXCLUSION_LIST)
    list(SORT SOURCE_EXCLUSION_LIST)
endif()

add_subdirectory("src")
if(BUILD_TESTS)
    add_subdirectory("tests")
endif()

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)
install(
    TARGETS tmpl
    COMPONENT libtmpl_Runtime
    EXPORT libtmpl_Runtime
    RUNTIME
    DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
    FILE_SET HEADERS
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}}
)
set(LIBTMPL_RUNTIME_CONFIG_FILE libtmpl_Runtime.cmake CACHE INTERNAL "")
install(
    EXPORT libtmpl_Runtime
    NAMESPACE tmpl::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
    FILE ${LIBTMPL_RUNTIME_CONFIG_FILE}
)
set(cmakeModulesDir cmake)
configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/libtmplConfig.cmake.in
    ${PROJECT_NAME}Config.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
    PATH_VARS cmakeModulesDir
    NO_SET_AND_CHECK_MACRO
    NO_CHECK_REQUIRED_COMPONENTS_MACRO
)
install(
    FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)
