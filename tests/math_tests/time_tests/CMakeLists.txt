cmake_minimum_required(VERSION 3.20)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../cmake")

if(UNIX AND NOT APPLE AND NOT CYGWIN AND SYSTEM_PROCESSOR STREQUAL "x86_64")
    include(FetchLinAsm)
endif()

include(FindGSL)

project(math_time_tests)

set(test_apps
    tmpl_abs_double_time_test
    tmpl_abs_float_time_test
    tmpl_abs_ldouble_time_test
    tmpl_arctan2_double_time_test
    tmpl_arctan2_float_time_test
    tmpl_arctan2_ldouble_time_test
    tmpl_arctan_double_time_test
    tmpl_arctan_float_time_test
    tmpl_arctan_ldouble_time_test
    tmpl_arctan_maclaurin_double_time_test
    tmpl_arctan_maclaurin_float_time_test
    tmpl_arctan_pade_double_time_test
    tmpl_arctan_pade_float_time_test
    tmpl_arctan_pade_ldouble_time_test
    tmpl_array_max_double_time_test
    tmpl_array_max_float_time_test
    tmpl_array_max_index_double_time_test
    tmpl_array_max_index_float_time_test
    tmpl_array_max_index_ldouble_time_test
    tmpl_array_max_ldouble_time_test
    tmpl_array_min_double_time_test
    tmpl_array_min_float_time_test
    tmpl_array_min_index_double_time_test
    tmpl_array_min_index_float_time_test
    tmpl_array_min_index_ldouble_time_test
    tmpl_array_min_ldouble_time_test
    tmpl_array_minmax_double_time_test
    tmpl_array_minmax_float_time_test
    tmpl_array_minmax_index_double_time_test
    tmpl_array_minmax_index_float_time_test
    tmpl_array_minmax_index_ldouble_time_test
    tmpl_array_minmax_ldouble_time_test
    tmpl_base2_mant_and_exp_double_time_test
    tmpl_base2_mant_and_exp_float_time_test
    tmpl_base2_mant_and_exp_ldouble_time_test
    tmpl_cbrt_double_time_test
    tmpl_cbrt_double_time_test_denormal_vals
    tmpl_cbrt_float_time_test
    tmpl_cbrt_ldouble_time_test
    tmpl_cbrt_pade_double_time_test
    tmpl_cbrt_pade_ldouble_time_test
    tmpl_copysign_double_time_test
    tmpl_copysign_float_time_test
    tmpl_copysign_ldouble_time_test
    tmpl_cos_double_time_test
    tmpl_cos_float_time_test
    tmpl_cos_ldouble_time_test
    tmpl_cosd_double_time_test
    tmpl_cosd_float_time_test
    tmpl_cosd_ldouble_time_test
    tmpl_cosh_double_time_test
    tmpl_cosh_float_time_test
    tmpl_cosh_pade_double_time_test
    tmpl_cospi_double_time_test
    tmpl_cospi_ldouble_time_test
    tmpl_dist_double_time_test
    tmpl_dist_float_time_test
    tmpl_dist_ldouble_time_test
    tmpl_exp_double_time_test
    tmpl_exp_float_time_test
    tmpl_floor_double_time_test
    tmpl_floor_float_time_test
    tmpl_floor_ldouble_time_test
    tmpl_log_double_time_test
    tmpl_log_double_time_test_big_vals
    tmpl_log_double_time_test_denormal_vals
    tmpl_log_double_time_test_near_1
    tmpl_log_float_time_test
    tmpl_log_float_time_test_big_vals
    tmpl_log_float_time_test_denormal_vals
    tmpl_log_float_time_test_near_1
    tmpl_log_ldouble_time_test
    tmpl_log_ldouble_time_test_big_vals
    tmpl_log_ldouble_time_test_denormal_vals
    tmpl_log_ldouble_time_test_near_1
    tmpl_mod_2_double_time_test
    tmpl_mod_2_float_time_test
    tmpl_mod_2_ldouble_time_test
    tmpl_mod_360_double_time_test
    tmpl_pow2_double_time_test
    tmpl_pow2_float_time_test
    tmpl_pow2_ldouble_time_test
    tmpl_sin_double_time_test
    tmpl_sin_float_time_test
    tmpl_sin_ldouble_time_test
    tmpl_sin_pade_double_time_test
    tmpl_sin_pade_pi_double_time_test
    tmpl_sincos_double_time_test
    tmpl_sind_double_time_test
    tmpl_sind_float_time_test
    tmpl_sind_ldouble_time_test
    tmpl_sinpi_double_time_test
    tmpl_sqrt_double_time_test
    tmpl_sqrt_double_time_test_big_vals
    tmpl_sqrt_double_time_test_denormal_vals
    tmpl_sqrt_double_time_test_near_1
    tmpl_sqrt_float_time_test
    tmpl_sqrt_float_time_test_big_vals
    tmpl_sqrt_float_time_test_denormal_vals
    tmpl_sqrt_float_time_test_near_1
    tmpl_sqrt_ldouble_time_test
    tmpl_sqrt_ldouble_time_test_big_vals
    tmpl_sqrt_ldouble_time_test_denormal_vals
    tmpl_sqrt_ldouble_time_test_near_1
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
        PRIVATE "${GSL_INCLUDE_DIRS}"
    )
    target_link_libraries(${app} PRIVATE tmpl::tmpl CONAN_LIB::GSL_gsl)
    if(UNIX)
        target_link_libraries(${app} PRIVATE m)
    endif()
endforeach()

if(UNIX AND SYSTEM_PROCESSOR STREQUAL "x86_64")
    set(linasm_compare_test_apps
        tmpl_log_double_time_test_vs_linasm
        tmpl_sin_double_time_test_vs_linasm
        tmpl_sqrt_double_time_test_vs_linasm
    )

    foreach(app ${linasm_compare_test_apps})
        add_executable(${app} ${app}.c)
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
    endforeach()
endif()

include(GNUInstallDirs)
install(
    TARGETS ${test_apps} ${linasm_compare_test_apps}
    RUNTIME
    DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
