cmake_minimum_required(VERSION 3.20)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../cmake")

if(UNIX
   AND NOT APPLE
   AND NOT CYGWIN
   AND SYSTEM_PROCESSOR STREQUAL "x86_64"
)
    include(FetchLinAsm)
endif()

include(FindGSL)

project(math_time_tests)

file(GLOB sources CONFIGURE_DEPENDS *.c)

set(linasm_compare_sources ${sources})
list(FILTER linasm_compare_sources INCLUDE REGEX .*linasm.*)
list(FILTER sources EXCLUDE REGEX .*linasm.*)
if(NOT "${CMAKE_C_COMPILER_ID}" STREQUAL "GNU" OR NOT EXISTS
                                                  "${CMAKE_CURRENT_SOURCE_DIR}/src/math/tmpl_sincos_double.c"
)
    # Exclude tests that use GCC builtins when not compiling with GCC
    list(REMOVE_ITEM sources "${CMAKE_CURRENT_SOURCE_DIR}/tmpl_sincos_double_time_test.c")
endif()

foreach(source ${sources})
    cmake_path(GET source STEM app)
    list(APPEND test_apps ${app})
    add_executable(${app} ${source})
    set_target_properties(${app} PROPERTIES INTERPROCEDURAL_OPTIMIZATION ${IPO_SUPPORTED})
    target_include_directories(
        ${app}
        PUBLIC "${TMPL_PARENT_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}"
        PRIVATE "${GSL_INCLUDE_DIRS}"
    )
    target_link_libraries(${app} PRIVATE tmpl::tmpl CONAN_LIB::GSL_gsl)
    if(UNIX)
        target_link_libraries(${app} PRIVATE m)
    endif()

    add_test(NAME test_${app} COMMAND ${app})
endforeach()

if(UNIX
   AND NOT APPLE
   AND NOT CYGWIN
   AND SYSTEM_PROCESSOR STREQUAL "x86_64"
)
    foreach(source ${linasm_compare_sources})
        cmake_path(GET source STEM app)
        list(APPEND test_apps ${app})
        add_executable(${app} ${source})
        set_target_properties(${app} PROPERTIES INTERPROCEDURAL_OPTIMIZATION ${IPO_SUPPORTED})
        target_include_directories(
            ${app}
            PUBLIC "${TMPL_PARENT_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}"
            PRIVATE "${linasm_INCLUDE_DIR}"
        )
        target_link_libraries(${app} PRIVATE tmpl::tmpl)
        if(UNIX)
            target_link_libraries(${app} PRIVATE m)
        endif()

        add_test(NAME test_${app} COMMAND ${app})
    endforeach()
endif()

include(GNUInstallDirs)
install(
    TARGETS ${test_apps}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
