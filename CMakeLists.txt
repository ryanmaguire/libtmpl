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

add_library(tmpl SHARED)
add_executable(tmpl_config config.c)
target_source(tmpl PRIVATE "include/tmpl_config.h")

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

# TODO: Check for incompatible requests. inline can't be used with -std=c89/c90.
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

# TODO: set up ASM support

# Build config.c and run to generate "include/tmpl_config.h"
add_custom_command(
    OUTPUT "include/tmpl_config.h"
    DEPENDS tmpl_config
    BYPRODUCTS "include/tmpl_config.h"
    COMMAND "$<TARGET_FILE:tmpl_config>"
    VERBATIM
)

target_include_directories(tmpl PUBLIC include)

add_subdirectory("src")

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
