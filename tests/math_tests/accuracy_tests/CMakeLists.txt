cmake_minimum_required(VERSION 3.20)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../cmake")

project(math_accuracy_tests)

set(test_apps
    tmpl_abs_double_accuracy_test
    tmpl_abs_float_accuracy_test
    tmpl_abs_ldouble_accuracy_test
    tmpl_arctan_double_accuracy_test
    tmpl_arctan_float_accuracy_test
    tmpl_arctan_ldouble_accuracy_test
    tmpl_floor_double_accuracy_test
    tmpl_log_double_accuracy_test
    tmpl_log_float_accuracy_test
    tmpl_log_ldouble_accuracy_test
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
