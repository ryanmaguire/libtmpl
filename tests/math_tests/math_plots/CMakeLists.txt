cmake_minimum_required(VERSION 3.20)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../cmake")

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    if(APPLE)
        include(gcc-macos)
    elseif(UNIX)
        include(gcc)
    endif()
endif()

project(math_plots_tests)

set(test_apps
    tmpl_arctan_double_diff_plot_gnuplotutils
    tmpl_arctan_double_gnuplotutils
    tmpl_arctan_float_diff_plot_gnuplotutils
    tmpl_arctan_float_gnuplotutils
    tmpl_arctan_ldouble_diff_plot_gnuplotutils
    tmpl_arctan_ldouble_gnuplotutils
    tmpl_arctan_maclaurin_double_diff_log_plot_gnuplotutils
    tmpl_arctan_maclaurin_float_diff_log_plot_gnuplotutils
    tmpl_arctan_pade_double_diff_log_plot_gnuplotutils
    tmpl_floor_double_diff_plot_gnuplotutils
    tmpl_log_double_diff_plot_near_one_gnuplotutils
    tmpl_log_double_gnuplotutils
    tmpl_log_float_gnuplotutils
    tmpl_log_ldouble_gnuplotutils
    tmpl_mod_2_double_gnuplotutils
    tmpl_mod_2_float_gnuplotutils.c # TODO correct file name
    tmpl_sin_double_diff_plot_gnuplotutils
    tmpl_sin_double_gnuplotutils
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
