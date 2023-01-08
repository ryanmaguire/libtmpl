cmake_minimum_required(VERSION 3.20)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../cmake")


if(UNIX AND NOT APPLE AND NOT CYGWIN AND SYSTEM_PROCESSOR STREQUAL "x86_64")
    include(FetchLinAsm)
endif()

project(vec3_time_tests)

file(GLOB sources CONFIGURE_DEPENDS *.c)

set(linasm_compare_sources ${sources})
list(FILTER linasm_compare_sources INCLUDE REGEX .*linasm.*)
list(FILTER sources EXCLUDE REGEX .*linasm.*)

foreach(source ${sources})
    cmake_path(GET source STEM app)
    list(APPEND test_apps ${app})
    add_executable(${app} ${source})
    set_target_properties(
        ${app}
        PROPERTIES INTERPROCEDURAL_OPTIMIZATION ${IPO_SUPPORTED}
    )
    target_include_directories(
        ${app}
        PUBLIC "${TMPL_PARENT_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}"
    )
    target_link_libraries(${app} PRIVATE tmpl::tmpl)
    if(UNIX)
        target_link_libraries(${app} PRIVATE m)
    endif()

    add_test(NAME test_${app} COMMAND ${app})
endforeach()

if(UNIX AND NOT APPLE AND NOT CYGWIN AND SYSTEM_PROCESSOR STREQUAL "x86_64")
    foreach(source ${linasm_compare_sources})
        cmake_path(GET source STEM app)
        list(APPEND test_apps ${app})
        add_executable(${app} ${source})
        set_target_properties(
            ${app}
            PROPERTIES INTERPROCEDURAL_OPTIMIZATION ${IPO_SUPPORTED}
        )
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
    RUNTIME
    DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
