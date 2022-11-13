cmake_minimum_required(VERSION 3.20)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../cmake")

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    if(APPLE)
        include(gcc-macos)
    elseif(UNIX)
        include(gcc)
    endif()
endif()

project(bytes_tests)

set(test_apps
    complex_compare_example
    complex_comparef_example
    complex_comparel_example
    complex_conjugate_example
    complex_conjugatef_example
    complex_conjugatel_example
    complex_cos_example
    complex_cosf_example
    complex_cosl_example
    complex_dist_example
    complex_distf_example
    complex_distl_example
    complex_divide_example
    complex_dividef_example
    complex_dividel_example
    complex_exp_example
    tmpl_complex_abs_example
    tmpl_complex_abs_squared_example
    tmpl_complex_absf_example
    tmpl_complex_absf_squared_example
    tmpl_complex_absl_example
    tmpl_complex_absl_squared_example
    tmpl_complex_add_example
    tmpl_complex_add_imag_example
    tmpl_complex_add_imagf_example
    tmpl_complex_add_imagl_example
    tmpl_complex_add_real_example
    tmpl_complex_add_realf_example
    tmpl_complex_add_reall_example
    tmpl_complex_addf_example
    tmpl_complex_addl_example
    tmpl_complex_argument_example
    tmpl_complex_argumentf_example
    tmpl_complex_argumentl_example
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
