cmake_minimum_required(VERSION 3.20)
list(APPEND CMAKE_MODULE_PATH "${TMPL_PARENT_DIR}/cmake")

project(polynomial_integer_time_tests)

file(GLOB sources CONFIGURE_DEPENDS *.c)

foreach(source ${sources})
    cmake_path(GET source STEM app)
    list(APPEND test_apps ${app})
    add_executable(${app} ${source})
    set_target_properties(
        ${app} PROPERTIES INTERPROCEDURAL_OPTIMIZATION ${IPO_SUPPORTED} )
    if(DEFINED CROSSCOMPILING_EMULATOR)
        set_target_properties(${app} PROPERTIES CROSSCOMPILING_EMULATOR ${CROSSCOMPILING_EMULATOR})
    endif()
    target_include_directories(${app} PUBLIC "${TMPL_PARENT_DIR}")
    target_link_libraries(${app} PRIVATE tmpl::tmpl)
    if(UNIX)
        target_link_libraries(${app} PRIVATE m)
    endif()

    add_test(NAME test_${app} COMMAND ${app})
endforeach()

include(GNUInstallDirs)
install(
    TARGETS ${test_apps}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
