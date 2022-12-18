cmake_minimum_required(VERSION 3.20)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../cmake")

project(math_tests_unit_tests)

set(test_apps
    tmpl_abs_double_unit_test_001
    tmpl_abs_double_unit_test_002
    tmpl_abs_float_unit_test_001
    tmpl_abs_float_unit_test_002
    tmpl_abs_ldouble_unit_test_001
    tmpl_abs_ldouble_unit_test_002
    tmpl_arctan2_double_unit_test_001
    tmpl_arctan2_double_unit_test_002
    tmpl_arctan2_double_unit_test_003
    tmpl_arctan2_double_unit_test_004
    tmpl_arctan2_double_unit_test_005
    tmpl_arctan2_double_unit_test_006
    tmpl_arctan2_double_unit_test_007
    tmpl_arctan2_double_unit_test_008
    tmpl_arctan2_double_unit_test_009
    tmpl_arctan2_double_unit_test_010
    tmpl_arctan2_double_unit_test_011
    tmpl_arctan2_double_unit_test_012
    tmpl_arctan2_float_unit_test_001
    tmpl_arctan2_float_unit_test_002
    tmpl_arctan2_float_unit_test_003
    tmpl_arctan2_float_unit_test_004
    tmpl_arctan2_float_unit_test_005
    tmpl_arctan2_float_unit_test_006
    tmpl_arctan2_float_unit_test_007
    tmpl_arctan2_float_unit_test_008
    tmpl_arctan2_float_unit_test_009
    tmpl_arctan2_float_unit_test_010
    tmpl_arctan2_float_unit_test_011
    tmpl_arctan2_float_unit_test_012
    tmpl_arctan2_ldouble_unit_test_001
    tmpl_arctan2_ldouble_unit_test_002
    tmpl_arctan2_ldouble_unit_test_003
    tmpl_arctan2_ldouble_unit_test_004
    tmpl_arctan2_ldouble_unit_test_005
    tmpl_arctan2_ldouble_unit_test_006
    tmpl_arctan2_ldouble_unit_test_007
    tmpl_arctan2_ldouble_unit_test_008
    tmpl_arctan2_ldouble_unit_test_009
    tmpl_arctan2_ldouble_unit_test_010
    tmpl_arctan2_ldouble_unit_test_011
    tmpl_arctan2_ldouble_unit_test_012
    tmpl_is_inf_double_unit_test_001
    tmpl_is_inf_double_unit_test_002
    tmpl_is_inf_float_unit_test_001
    tmpl_is_inf_float_unit_test_002
    tmpl_is_inf_ldouble_unit_test_001
    tmpl_is_inf_ldouble_unit_test_002
    tmpl_is_nan_double_unit_test_001
    tmpl_is_nan_double_unit_test_002
    tmpl_is_nan_float_unit_test_001
    tmpl_is_nan_float_unit_test_002
    tmpl_is_nan_ldouble_unit_test_001
    tmpl_is_nan_ldouble_unit_test_002
    tmpl_is_nan_or_inf_double_unit_test_001
    tmpl_is_nan_or_inf_double_unit_test_002
    tmpl_is_nan_or_inf_float_unit_test_001
    tmpl_is_nan_or_inf_float_unit_test_002
    tmpl_is_nan_or_inf_ldouble_unit_test_001
    tmpl_is_nan_or_inf_ldouble_unit_test_002
)

foreach(app ${test_apps})
    add_executable(${app} ${app}.c)
    set_target_properties(${app} PROPERTIES INTERPROCEDURAL_OPTIMIZATION ${IPO_SUPPORTED})
    target_include_directories(${app} PUBLIC "${TMPL_PARENT_DIR}")
    target_link_libraries(${app} PRIVATE tmpl::tmpl)
    if(UNIX)
        target_link_libraries(${app} PRIVATE m)
    endif()
endforeach()

include(GNUInstallDirs)
install(TARGETS ${test_apps} RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
