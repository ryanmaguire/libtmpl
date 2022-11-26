cmake_minimum_required(VERSION 3.20)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../cmake")

project(complex_time_tests)

set(test_apps
    tmpl_complex_abs_double_time_test
    tmpl_complex_abs_float_time_test
    tmpl_complex_abs_ldouble_time_test
    tmpl_complex_abs_squared_double_time_test
    tmpl_complex_abs_squared_float_time_test
    tmpl_complex_abs_squared_ldouble_time_test
    tmpl_complex_add_imag_time_test
    tmpl_complex_add_imagf_time_test
    tmpl_complex_add_imagl_time_test
    tmpl_complex_add_real_time_test
    tmpl_complex_add_realf_time_test
    tmpl_complex_add_reall_time_test
    tmpl_complex_add_time_test
    tmpl_complex_addf_time_test
    tmpl_complex_addl_time_test
    tmpl_complex_addto_time_test
    tmpl_complex_argument_time_test
    tmpl_complex_argumentf_time_test
    tmpl_complex_argumentl_time_test
    tmpl_complex_quick_abs_time_test
)

foreach(app ${test_apps})
    add_executable(${app} ${app}.c)
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
endforeach()

include(GNUInstallDirs)
install(
    TARGETS ${test_apps}
    RUNTIME
    DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
