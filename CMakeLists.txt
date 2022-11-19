cmake_minimum_required(VERSION 3.23)
list(
    APPEND
    CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake
    ${CMAKE_CURRENT_BINARY_DIR}
)
include(ParseCStandard)

option(
    OMP
    "Compile with `OpenMP` support (highly recommended).
**WARNING** Apple's version of clang does **NOT** support OpenMP, and the `-fopenmp` option will result in an error.
Homebrew has versions of clang and gcc that do support OpenMP."
    TRUE
)
option(
    LIBTMPL_NO_INLINE
    "Do not use any inline code. This results in a slightly smaller `libtmpl.so` file, but several
functions become significantly slower (not recommended). If your compiler does not support `C99` or higher, and
does not support the `gcc` `inline` extension, enable this option."
    FALSE
)
option(
    LIBTMPL_NO_MATH
    "Do not use `libtmpl`'s implementation of `libm`, the C standard library for mathematical tools,
instead using your compilers implementation. This may be recommended. Tests against `glibc`, `FreeBSD libc`, and
`MSVC`'s implementation of `libm` show that `libtmpl` can be significantly faster (all functions have benchmarks
in the `tests/` directory and you may see for yourself), but this has only been tested on the architectures supported
by the Debian GNU/Linux operating system. Users of other architectures may wish to use their default `libm`. Also, if
your compiler does not support the `IEEE-754` standard (most do), or does not support type-punning for `union`, the
portable algorithms (algorithms that do not use `IEEE-754` or type-punning) are much slower. In these instances you
may wish to use the default `libm`."
    TRUE
)
option(
    LIBTMPL_NO_IEEE
    "Disable use of the `IEEE` formats for `float` and `double`. The `config.c` file should detect if your
compiler supports this, and type-punning for `union`, so you should not need to set this option manually
(not recommended)."
    FALSE
)
option(
    LIBTMPL_NO_ASM
    "Only applicable is `LIBTMPL_NO_MATH` is not set, and for `x86_64/amd64/arm64/armv7l` machines. Some functions,
like `sqrt`, can be handle efficiently in assembly code. If you wish to use only C code, set this option
(not recommended)."
    FALSE
)
option(
    LIBTMPL_NO_BUILTIN
    "Only applicable is `LIBTMPL_NO_MATH` and `LIBTMPL_NO_ASM` are not set, and only for `x86_64/amd64/arm64` machines.
If you are using `gcc`, `clang`, or `pcc`, you can take adventage of several built-in functions like `sincos`.
This is handled in assembly code. If you're not using a compiler that has these built-in functions, set this option
(not recommended)."
    TRUE
)
option(
    LIBTMPL_FASM
    "Use the flat assembler instead of the assembly language used by `gcc` and `clang`. You must have `fasm`
installed to use this. This option is ignored if `LIBTMPL_NO_ASM=1` is set."
    TRUE
)

option(LIBTMPL_NO_LONGLONG "" FALSE)
option(LIBTMPL_NO_INT "" FALSE)
option(LIBTMPL_BUILD_TESTS "Set to TRUE to enable the building of tests" FALSE)
option(
    LIBTMPL_BUILD_EXAMPLES
    "Set to TRUE to enable the building of examples"
    FALSE
)
option(LIBTMPL_ENABLE_VERBOSE "" FALSE)

if(NOT DEFINED LIBTMPL_STDVER)
    set(LIBTMPL_STDVER "-std=c89" CACHE STRING "" FORCE)
endif()

# Download automatically, you can also just copy the conan.cmake file
if(NOT EXISTS "${CMAKE_CURRENT_BINARY_DIR}/conan.cmake")
    message(
        STATUS
        "Downloading conan.cmake from https://github.com/conan-io/cmake-conan"
    )
    file(
        DOWNLOAD
            "https://raw.githubusercontent.com/conan-io/cmake-conan/master/conan.cmake"
            "${CMAKE_CURRENT_BINARY_DIR}/conan.cmake"
    )
endif()

project(libtmpl LANGUAGES C)

include(${CMAKE_CURRENT_BINARY_DIR}/conan.cmake)

conan_cmake_autodetect(settings)

conan_cmake_install(PATH_OR_REFERENCE ${CMAKE_CURRENT_SOURCE_DIR}
                    BUILD missing
                    REMOTE conancenter
                    SETTINGS ${settings}
)

cmake_path(GET CMAKE_CURRENT_SOURCE_DIR PARENT_PATH TMPL_PARENT_DIR)
include(FindBoost)
add_library(tmpl SHARED)
add_library(tmpl::tmpl ALIAS tmpl)
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
# Copy the export header to include/
add_custom_command(
    TARGET tmpl
    POST_BUILD
    COMMAND
        ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/include/tmpl_exports.h ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set_c_standard(TARGET tmpl
    STDVER "${LIBTMPL_STDVER}"
    ENABLE_VERBOSE ${LIBTMPL_ENABLE_VERBOSE}
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

if(LIBTMPL_NO_LONGLONG)
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

if(NOT LIBTMPL_NO_INLINE)
    if(LIBTMPL_STDVER STREQUAL "-std=c89")
        message(
            FATAL_ERROR
            "Error: inline mode cannot be used with C89.\n        Set -std to a version supporting inline."
        )
    endif()

    if(LIBTMPL_STDVER STREQUAL "-std=c90")
        message(
            FATAL_ERROR
            "Error: inline mode cannot be used with C90.\n        Set -std to a version supporting inline."
        )
    endif()
endif()

if(LIBTMPL_NO_MATH)
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

if(NOT LIBTMPL_NO_INLINE)
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

if(LIBTMPL_NO_IEEE)
    target_compile_definitions(tmpl_config PUBLIC TMPL_SET_TMPL_USE_IEEE_FALSE)
endif()

if(LIBTMPL_NO_INT)
    target_compile_definitions(tmpl_config PUBLIC TMPL_SET_NO_INT)
endif()

string(TOLOWER "${CMAKE_SYSTEM_PROCESSOR}" system_processor)
set(X86_64_ARCHES "amd64;x86_64")
set(ARM64_ARCHES "aarch64;arm64")
set(ARMHF_ARCHES "armv7l;")

if(NOT LIBTMPL_NO_ASM)
    if(system_processor IN_LIST X86_64_ARCHES)
        enable_language(ASM)

        if(NOT LIBTMPL_NO_BUILTIN)
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

        if(LIBTMPL_FASM)
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

        if(NOT LIBTMPL_NO_BUILTIN)
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
if(LIBTMPL_BUILD_TESTS)
    add_subdirectory("tests")
endif()

if(LIBTMPL_BUILD_EXAMPLES)
    add_subdirectory("examples")
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
