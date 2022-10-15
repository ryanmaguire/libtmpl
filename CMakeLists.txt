option(OMP "User OpenMP, if available" TRUE)
option(NO_INLINE "" TRUE)
option(NO_MATH "" TRUE)
option(NO_IEEE "" TRUE)
option(NO_ASM "" TRUE)
option(NO_BUILTIN "" TRUE)
option(FASM "" TRUE)

project(libtmpl_library)

add_library(tmpl SHARED)

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

if(NO_MATH)
    # Do not use libtmpl's libm implementation

    # TODO what to do for other systems?
    if(UNIX)
        target_link_libraries(tmpl PRIVATE m)
    endif()
    # TODO: set up file exclusions
else()
    target_compile_definitions(tmpl PUBLIC TMPL_SET_USE_MATH_TRUE)
endif()

if(NO_INLINE)
    target_compile_definitions(tmpl PUBLIC TMPL_SET_INLINE_TRUE)
else()
    # TODO: set up file exclusions
endif()

if(NO_IEEE)
    target_compile_definitions(tmpl PUBLIC TMPL_SET_TMPL_USE_IEEE_FALSE)
endif()

if(NO_INT)
    target_compile_definitions(tmpl PUBLIC TMPL_SET_NO_INT)
endif()

# TODO: set up ASM support

#target_compile_definitions(tmpl PUBLIC TMPL_USE_INLINE=$<IF:${NO_INLINE},true_string,false_string>)

target_include_directories(tmpl PUBLIC include)

add_subdirectory("src")
