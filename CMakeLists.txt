cmake_minimum_required(VERSION 3.23)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake ${CMAKE_CURRENT_BINARY_DIR})
include(ParseCStandard)

option(LIBTMPL_USE_OMP "Compile with `OpenMP` support (highly recommended).
**WARNING** Apple's version of clang does **NOT** support OpenMP, and the `-fopenmp` option will result in an error.
Homebrew has versions of clang and gcc that do support OpenMP." TRUE
)
option(
    LIBTMPL_USE_INLINE "Use inline code. If disabled, this results in a slightly smaller `libtmpl.so` file, but several
functions become significantly slower (not recommended). If your compiler does not support `C99` or higher, and
does not support the `gcc` `inline` extension, set this option to FALSE." TRUE
)
option(
    LIBTMPL_USE_MATH
    "Use `libtmpl`'s implementation of `libm`, the C standard library for mathematical tools,
instead using your compiler's implementation. This may be recommended. Tests against `glibc`, `FreeBSD libc`, and
`MSVC`'s implementation of `libm` show that `libtmpl` can be significantly faster (all functions have benchmarks
in the `tests/` directory and you may see for yourself), but this has only been tested on the architectures supported
by the Debian GNU/Linux operating system. Users of other architectures may wish to use their default `libm`. Also, if
your compiler does not support the `IEEE-754` standard (most do), or does not support type-punning for `union`, the
portable algorithms (algorithms that do not use `IEEE-754` or type-punning) are much slower. In these instances you
may wish to use the default `libm`."
    TRUE
)
option(
    LIBTMPL_USE_IEEE
    "Enable use of the `IEEE` formats for `float` and `double`. The `config.c` file should detect if your
compiler supports this, and type-punning for `union`, so you should not need to set this option manually
(not recommended)."
    TRUE
)
option(
    LIBTMPL_USE_ASM
    "Only applicable is `LIBTMPL_USE_MATH` is FALSE, and for `x86_64/amd64/arm64/armv7l` machines. Some functions,
like `sqrt`, can be handle efficiently in assembly code. If you wish to use only C code, set this option to FALSE
(not recommended)."
    TRUE
)
option(
    LIBTMPL_USE_BUILTIN
    "Only applicable is `LIBTMPL_USE_MATH` and `LIBTMPL_USE_ASM` are TRUE, and only for `x86_64/amd64/arm64` machines.
If you are using `gcc`, `clang`, or `pcc`, you can take adventage of several built-in functions like `sincos`.
This is handled in assembly code. If you're not using a compiler that has these built-in functions, set this option to
FALSE (not recommended)."
    TRUE
)
option(LIBTMPL_USE_FASM
       "Use the flat assembler instead of the assembly language used by `gcc` and `clang`. You must have `fasm`
installed to use this. This option is ignored if `LIBTMPL_USE_ASM` is FALSE." TRUE
)

option(LIBTMPL_USE_LONGLONG "" TRUE)
option(LIBTMPL_USE_INT "" TRUE)
option(LIBTMPL_USE_MEMCPY "" TRUE)
option(LIBTMPL_BUILD_TESTS "Set to TRUE to enable the building of tests." FALSE)
option(LIBTMPL_BUILD_EXAMPLES "Set to TRUE to enable the building of examples." FALSE)
option(LIBTMPL_ENABLE_VERBOSE "" FALSE)
option(LIBTMPL_INSTALL "Set to TRUE to enable the install rules for libtmpl." TRUE)

if(NOT DEFINED LIBTMPL_STDVER)
    set(LIBTMPL_STDVER
        "-std=c89"
        CACHE STRING "" FORCE
    )
endif()

# Download automatically, you can also just copy the conan.cmake file
if((LIBTMPL_BUILD_TESTS OR LIBTMPL_BUILD_EXAMPLES) AND NOT EXISTS "${CMAKE_CURRENT_BINARY_DIR}/conan.cmake")
    message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
    file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/0.18.1/conan.cmake"
         "${CMAKE_BINARY_DIR}/conan.cmake" TLS_VERIFY ON
    )
endif()

# Construct file lists
file(
    GLOB_RECURSE headers
    LIST_DIRECTORIES FALSE
    *.h
)
configure_file(cmake/headerList.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/headerList.cmake @ONLY)

file(
    GLOB_RECURSE sources
    LIST_DIRECTORIES FALSE
    *.c
)
configure_file(cmake/sourceList.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/sourceList.cmake @ONLY)

project(libtmpl LANGUAGES C)

if(LIBTMPL_BUILD_TESTS OR LIBTMPL_BUILD_EXAMPLES)
    include(${CMAKE_CURRENT_BINARY_DIR}/conan.cmake)

    if(DEFINED ENV{CONAN_CMAKE_SYSTEM_PROCESSOR})
        # We're cross compiling
        conan_cmake_autodetect(settings)

        conan_cmake_install(
            PATH_OR_REFERENCE ${CMAKE_CURRENT_SOURCE_DIR}
            BUILD missing
            REMOTE conancenter SETTINGS_BUILD "${settings}" PROFILE_HOST "${CONAN_PROFILE_FILE}"
        )
    else()
        conan_cmake_autodetect(settings)

        conan_cmake_install(
            PATH_OR_REFERENCE ${CMAKE_CURRENT_SOURCE_DIR}
            BUILD missing
            REMOTE conancenter
            SETTINGS ${settings}
            PROFILE "${CONAN_PROFILE_FILE}"
        )
    endif()
endif()

cmake_path(GET CMAKE_CURRENT_SOURCE_DIR PARENT_PATH TMPL_PARENT_DIR)

add_library(tmpl SHARED)
add_library(tmpl::tmpl ALIAS tmpl)
target_include_directories(
    tmpl PUBLIC "$<INSTALL_INTERFACE:include>" "$<BUILD_INTERFACE:${TMPL_PARENT_DIR}>"
                "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>"
)

if(MSVC)
    target_compile_options(tmpl PRIVATE /MP)
endif()

# Build config.c and run to generate "include/tmpl_config.h"
add_executable(tmpl_config config.c)
include(CMakePrintHelpers)
cmake_print_variables(CMAKE_FIND_ROOT_PATH CMAKE_SYSROOT CROSSCOMPILING_EMULATOR CMAKE_CROSSCOMPILING)
add_custom_command(
    OUTPUT "include/tmpl_config.h" "include/tmpl_inttype.h" "include/tmpl_limits.h"
    DEPENDS tmpl_config
    COMMAND ${CROSSCOMPILING_EMULATOR} "$<TARGET_FILE:tmpl_config>"
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/include/tmpl_config.h
            ${CMAKE_CURRENT_SOURCE_DIR}/include
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/include/tmpl_inttype.h
            ${CMAKE_CURRENT_SOURCE_DIR}/include
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/include/tmpl_limits.h
            ${CMAKE_CURRENT_SOURCE_DIR}/include
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    VERBATIM
)

target_sources(
    tmpl PUBLIC FILE_SET HEADERS BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_BINARY_DIR}/include
)
add_subdirectory("include")
# Copy the export header to include/
add_custom_command(
    TARGET tmpl
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/include/tmpl_exports.h
            ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set_c_standard(TARGET tmpl STDVER "${LIBTMPL_STDVER}" ENABLE_VERBOSE ${LIBTMPL_ENABLE_VERBOSE})

include(CheckIPOSupported)
# Optional IPO. Do not use IPO if it's not supported by compiler.
check_ipo_supported(RESULT IPO_SUPPORTED OUTPUT IPO_CHECK_OUTPUT)
if(IPO_SUPPORTED)
    message(STATUS "Interprocedural Optimization/Link-Time Optimization is supported.")
else()
    message(WARNING "Interprocedural Optimization/Link-Time Optimization is not supported: ${IPO_CHECK_OUTPUT}")
endif()

set_target_properties(tmpl PROPERTIES INTERPROCEDURAL_OPTIMIZATION ${IPO_SUPPORTED} POSITION_INDEPENDENT_CODE TRUE)

if(NOT LIBTMPL_USE_LONGLONG)
    target_compile_definitions(tmpl_config PUBLIC TMPL_SET_LONGLONG_FALSE)
    list(APPEND SOURCE_EXCLUSION_LIST "tmpl_abs_llong.c")
endif()

if(LIBTMPL_USE_MEMCPY)
    target_compile_definitions(tmpl_config PUBLIC TMPL_SET_USE_MEMCPY_TRUE)
endif()

if(LIBTMPL_USE_OMP)
    # Build with OpenMP, if it is supported by the toolchain
    find_package(OpenMP)
    if(OpenMP_C_FOUND)
        message(STATUS "OpenMP ${OpenMP_C_VERSION} found")
        target_link_libraries(tmpl PUBLIC OpenMP::OpenMP_C)
    else()
        message(WARNING "OpenMP was requested, but OpenMP support was not detected for this compiler: \
            ${CMAKE_C_COMPILER_ID} ${CMAKE_C_COMPILER_VERSION}"
        )
    endif()
endif()

if(LIBTMPL_USE_INLINE)
    if(LIBTMPL_STDVER STREQUAL "-std=c89")
        message(
            FATAL_ERROR "Error: inline mode cannot be used with C89.\n        Set -std to a version supporting inline."
        )
    endif()

    if(LIBTMPL_STDVER STREQUAL "-std=c90")
        message(
            FATAL_ERROR "Error: inline mode cannot be used with C90.\n        Set -std to a version supporting inline."
        )
    endif()
endif()

if(NOT LIBTMPL_USE_MATH)
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
        "tmpl_arccos_double.c"
        "tmpl_arccos_float.c"
        "tmpl_arccos_ldouble.c"
        "tmpl_arcsin_double.c"
        "tmpl_arcsin_float.c"
        "tmpl_arcsin_ldouble.c"
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

if(LIBTMPL_USE_INLINE)
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
        "tmpl_arccos_maclaurin_double.c"
        "tmpl_arccos_maclaurin_float.c"
        "tmpl_arccos_maclaurin_ldouble.c"
        "tmpl_arccos_pade_double.c"
        "tmpl_arccos_pade_float.c"
        "tmpl_arccos_pade_ldouble.c"
        "tmpl_arccos_rat_remez_double.c"
        "tmpl_arccos_rat_remez_float.c"
        "tmpl_arccos_rat_remez_ldouble.c"
        "tmpl_arccos_tail_end_double.c"
        "tmpl_arccos_tail_end_float.c"
        "tmpl_arccos_tail_end_ldouble.c"
        "tmpl_arcsin_maclaurin_double.c"
        "tmpl_arcsin_maclaurin_float.c"
        "tmpl_arcsin_maclaurin_ldouble.c"
        "tmpl_arcsin_pade_double.c"
        "tmpl_arcsin_pade_float.c"
        "tmpl_arcsin_pade_ldouble.c"
        "tmpl_arcsin_rat_remez_double.c"
        "tmpl_arcsin_rat_remez_float.c"
        "tmpl_arcsin_rat_remez_ldouble.c"
        "tmpl_arcsin_tail_end_double.c"
        "tmpl_arcsin_tail_end_float.c"
        "tmpl_arcsin_tail_end_ldouble.c"
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
        "tmpl_bessel_i0_asymptotic_double.c"
        "tmpl_bessel_i0_asymptotic_float.c"
        "tmpl_bessel_i0_chebyshev_double.c"
        "tmpl_bessel_i0_chebyshev_float.c"
        "tmpl_bessel_i0_maclaurin_double.c"
        "tmpl_bessel_i0_maclaurin_float.c"
        "tmpl_cbrt_pade_double.c"
        "tmpl_cbrt_pade_float.c"
        "tmpl_cbrt_pade_ldouble.c"
        "tmpl_cbrt_taylor_double.c"
        "tmpl_cbrt_taylor_float.c"
        "tmpl_cbrt_taylor_ldouble.c"
        "tmpl_complex_abs_double.c"
        "tmpl_complex_abs_float.c"
        "tmpl_complex_abs_ldouble.c"
        "tmpl_complex_abs_squared_double.c"
        "tmpl_complex_abs_squared_float.c"
        "tmpl_complex_abs_squared_ldouble.c"
        "tmpl_complex_add_double.c"
        "tmpl_complex_add_float.c"
        "tmpl_complex_add_ldouble.c"
        "tmpl_complex_add_imag_double.c"
        "tmpl_complex_add_imag_float.c"
        "tmpl_complex_add_imag_ldouble.c"
        "tmpl_complex_add_real_double.c"
        "tmpl_complex_add_real_float.c"
        "tmpl_complex_add_real_ldouble.c"
        "tmpl_complex_addto_double.c"
        "tmpl_complex_addto_float.c"
        "tmpl_complex_addto_ldouble.c"
        "tmpl_complex_addto_imag_double.c"
        "tmpl_complex_addto_imag_float.c"
        "tmpl_complex_addto_imag_ldouble.c"
        "tmpl_complex_addto_real_double.c"
        "tmpl_complex_addto_real_float.c"
        "tmpl_complex_addto_real_ldouble.c"
        "tmpl_complex_argument_double.c"
        "tmpl_complex_argument_float.c"
        "tmpl_complex_argument_ldouble.c"
        "tmpl_complex_conjugate_double.c"
        "tmpl_complex_conjugate_float.c"
        "tmpl_complex_conjugate_ldouble.c"
        "tmpl_complex_conjugateself_double.c"
        "tmpl_complex_conjugateself_float.c"
        "tmpl_complex_conjugateself_ldouble.c"
        "tmpl_complex_dist_double.c"
        "tmpl_complex_dist_float.c"
        "tmpl_complex_dist_ldouble.c"
        "tmpl_complex_dist_squared_double.c"
        "tmpl_complex_dist_squared_float.c"
        "tmpl_complex_dist_squared_ldouble.c"
        "tmpl_complex_expi_double.c"
        "tmpl_complex_expi_float.c"
        "tmpl_complex_expi_ldouble.c"
        "tmpl_complex_expipi_double.c"
        "tmpl_complex_expipi_float.c"
        "tmpl_complex_expipi_ldouble.c"
        "tmpl_complex_multiply_double.c"
        "tmpl_complex_multiply_float.c"
        "tmpl_complex_multiply_ldouble.c"
        "tmpl_complex_multiply_imag_double.c"
        "tmpl_complex_multiply_imag_float.c"
        "tmpl_complex_multiply_imag_ldouble.c"
        "tmpl_complex_multiply_real_double.c"
        "tmpl_complex_multiply_real_float.c"
        "tmpl_complex_multiply_real_ldouble.c"
        "tmpl_complex_polar_double.c"
        "tmpl_complex_polar_float.c"
        "tmpl_complex_polar_ldouble.c"
        "tmpl_complex_quick_abs_double.c"
        "tmpl_complex_quick_abs_float.c"
        "tmpl_complex_quick_abs_ldouble.c"
        "tmpl_complex_quick_dist_double.c"
        "tmpl_complex_quick_dist_float.c"
        "tmpl_complex_quick_dist_ldouble.c"
        "tmpl_copysign_float.c"
        "tmpl_copysign_double.c"
        "tmpl_copysign_ldouble.c"
        "tmpl_cosd_maclaurin_double.c"
        "tmpl_cosd_maclaurin_float.c"
        "tmpl_cosd_maclaurin_ldouble.c"
        "tmpl_cosh_maclaurin_double.c"
        "tmpl_cosh_maclaurin_float.c"
        "tmpl_cosh_maclaurin_ldouble.c"
        "tmpl_cosh_pade_double.c"
        "tmpl_cosh_pade_float.c"
        "tmpl_cosh_pade_ldouble.c"
        "tmpl_exp_maclaurin_double.c"
        "tmpl_exp_maclaurin_float.c"
        "tmpl_exp_maclaurin_ldouble.c"
        "tmpl_exp_pade_double.c"
        "tmpl_exp_pade_float.c"
        "tmpl_exp_pade_ldouble.c"
        "tmpl_cospi_maclaurin_double.c"
        "tmpl_cospi_maclaurin_float.c"
        "tmpl_cospi_maclaurin_ldouble.c"
        "tmpl_exp_remez_double.c"
        "tmpl_exp_remez_float.c"
        "tmpl_exp_remez_ldouble.c"
        "tmpl_dist_float.c"
        "tmpl_dist_double.c"
        "tmpl_dist_ldouble.c"
        "tmpl_erf_asymptotic_double.c"
        "tmpl_erf_chebyshev_double.c"
        "tmpl_erf_maclaurin_double.c"
        "tmpl_erf_pade_double.c"
        "tmpl_exp_neg_kernel_double.c"
        "tmpl_exp_neg_kernel_float.c"
        "tmpl_exp_neg_kernel_ldouble.c"
        "tmpl_exp_pos_kernel_double.c"
        "tmpl_exp_pos_kernel_float.c"
        "tmpl_exp_pos_kernel_ldouble.c"
        "tmpl_is_inf_float.c"
        "tmpl_is_inf_double.c"
        "tmpl_is_inf_ldouble.c"
        "tmpl_is_nan_float.c"
        "tmpl_is_nan_double.c"
        "tmpl_is_nan_ldouble.c"
        "tmpl_positive_difference_double.c"
        "tmpl_positive_difference_float.c"
        "tmpl_positive_difference_ldouble.c"
        "tmpl_sin_pade_double.c"
        "tmpl_sin_pade_float.c"
        "tmpl_sin_pade_ldouble.c"
        "tmpl_sin_pade_pi_double.c"
        "tmpl_sin_pade_pi_float.c"
        "tmpl_sin_pade_pi_ldouble.c"
        "tmpl_sind_maclaurin_double.c"
        "tmpl_sind_maclaurin_float.c"
        "tmpl_sind_maclaurin_ldouble.c"
        "tmpl_sinpi_maclaurin_double.c"
        "tmpl_sinpi_maclaurin_float.c"
        "tmpl_sinpi_maclaurin_ldouble.c"
        "tmpl_sin_very_small_double.c"
        "tmpl_two_vector_l2_norm_double.c"
        "tmpl_two_vector_l2_norm_float.c"
        "tmpl_two_vector_l2_norm_ldouble.c"
    )
endif()

if(NOT LIBTMPL_USE_IEEE)
    target_compile_definitions(tmpl_config PUBLIC TMPL_SET_TMPL_USE_IEEE_FALSE)
endif()

if(NOT LIBTMPL_USE_INT)
    target_compile_definitions(tmpl_config PUBLIC TMPL_SET_NO_INT)
endif()

string(TOLOWER "${CMAKE_SYSTEM_PROCESSOR}" system_processor)
set(X86_64_ARCHES "amd64;x86_64")
set(X86_ARCHES "i386;x86")
set(ARM64_ARCHES "aarch64;arm64")
set(ARMHF_ARCHES "armv7l")

if(LIBTMPL_USE_ASM)
    if(system_processor IN_LIST X86_64_ARCHES)
        enable_language(ASM)

        if(LIBTMPL_USE_FASM)
            if(UNIX
               AND NOT APPLE
               AND NOT CYGWIN
               AND ${CMAKE_SIZEOF_VOID_P} EQUAL 8
            )
                enable_language(ASM_FASM)
                add_subdirectory("src/assembly/fasm")
            else()
                message(WARNING "FASM is only supported for 64-bit Linux builds")
            endif()
        elseif()
            add_subdirectory("src/assembly/x86_64")
        endif()
    elseif(system_processor IN_LIST ARM64_ARCHES)
        enable_language(ASM)

        add_subdirectory("src/assembly/aarch64")
    elseif(system_processor IN_LIST ARMHF_ARCHES)
        enable_language(ASM)

        add_subdirectory("src/assembly/armv7l")
    elseif(system_processor IN_LIST X86_ARCHES)
        enable_language(ASM)

        add_subdirectory("src/assembly/i386")
    endif()
endif()

list(LENGTH SOURCE_EXCLUSION_LIST SOURCE_EXCLUSION_LIST_SIZE)
if(SOURCE_EXCLUSION_LIST_SIZE GREATER 1)
    list(REMOVE_DUPLICATES SOURCE_EXCLUSION_LIST)
    list(SORT SOURCE_EXCLUSION_LIST)
endif()

add_subdirectory("src")
if(LIBTMPL_BUILD_TESTS AND NOT DEFINED CROSSCOMPILING_EMULATOR)
    enable_testing()
    add_subdirectory("tests")
endif()

if(LIBTMPL_BUILD_EXAMPLES)
    add_subdirectory("examples")
endif()

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)
if(LIBTMPL_INSTALL)
    install(
        TARGETS tmpl
        COMPONENT libtmpl_Runtime
        EXPORT libtmpl_Runtime
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
                FILE_SET HEADERS
                DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
        INCLUDES
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}}
    )

    set(LIBTMPL_RUNTIME_CONFIG_FILE
        libtmpl_Runtime.cmake
        CACHE INTERNAL ""
    )
    install(
        EXPORT libtmpl_Runtime
        NAMESPACE tmpl::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
        FILE ${LIBTMPL_RUNTIME_CONFIG_FILE}
    )
    set(cmakeModulesDir cmake)
    configure_package_config_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/cmake/libtmplConfig.cmake.in ${PROJECT_NAME}Config.cmake
        INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
        PATH_VARS cmakeModulesDir
        NO_SET_AND_CHECK_MACRO NO_CHECK_REQUIRED_COMPONENTS_MACRO
    )
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
            DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
    )
endif()
