cmake_minimum_required(VERSION 3.20)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../cmake")

project(bytes_tests)

set(test_apps
    tmpl_add_polynomial_z_example_001
    tmpl_add_polynomial_z_example_002
    tmpl_add_polynomial_z_example_003
    tmpl_add_polynomial_z_example_004
    tmpl_add_polynomial_z_example_005
    tmpl_add_polynomial_z_example_006
    tmpl_deriv_polynomial_z_example_001
    tmpl_deriv_polynomial_z_example_002
    tmpl_deriv_polynomial_z_example_003
    tmpl_multiply_polynomial_z_example_001
    tmpl_multiply_polynomial_z_example_002
    tmpl_multiply_polynomial_z_example_003
    tmpl_multiply_polynomial_z_example_004
    tmpl_multiply_polynomial_z_example_005
    tmpl_subtract_polynomial_z_example_001
    tmpl_subtract_polynomial_z_example_002
)

foreach(app ${test_apps})
    add_executable(${app} ${app}.c)
    set_target_properties(
        ${app}
        PROPERTIES INTERPROCEDURAL_OPTIMIZATION ${IPO_SUPPORTED}
    )
    target_include_directories(${app} PUBLIC "${TMPL_PARENT_DIR}")
    target_link_libraries(${app} PRIVATE tmpl::tmpl)
    if(UNIX)
        target_link_libraries(${app} PRIVATE m)
    endif()
endforeach()

include(GNUInstallDirs)
install(
    TARGETS ${test_apps}
    RUNTIME
    DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
