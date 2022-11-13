cmake_minimum_required(VERSION 3.20)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../cmake")

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    if(APPLE)
        include(gcc-macos)
    elseif(UNIX)
        include(gcc)
    endif()
endif()

if(UNIX AND SYSTEM_PROCESSOR STREQUAL "x86_64")
    include(FetchLinAsm)
endif()

project(vec3_time_tests)

set(test_apps
    tmpl_three_vector_add_ldouble_huge_time_test
    tmpl_three_vector_add_ldouble_small_time_test
    tmpl_three_vector_add_to_ldouble_huge_time_test
    tmpl_three_vector_add_to_ldouble_small_time_test
    tmpl_three_vector_cross_product_ldouble_huge_time_test
    tmpl_three_vector_cross_product_ldouble_small_time_test
    tmpl_three_vector_cross_with_ldouble_huge_time_test
    tmpl_three_vector_cross_with_ldouble_small_time_test
    tmpl_three_vector_dot_product_ldouble_huge_time_test
    tmpl_three_vector_dot_product_ldouble_small_time_test
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

if(UNIX AND SYSTEM_PROCESSOR STREQUAL "x86_64")
    set(linasm_test_apps
        tmpl_three_vector_add_double_huge_time_test_vs_linasm
        tmpl_three_vector_add_double_small_time_test_vs_linasm
        tmpl_three_vector_add_float_huge_time_test_vs_linasm
        tmpl_three_vector_add_float_small_time_test_vs_linasm
        tmpl_three_vector_add_to_double_huge_time_test_vs_linasm
        tmpl_three_vector_add_to_double_small_time_test_vs_linasm
        tmpl_three_vector_add_to_float_huge_time_test_vs_linasm
        tmpl_three_vector_add_to_float_small_time_test_vs_linasm
        tmpl_three_vector_cross_product_double_huge_time_test_vs_linasm
        tmpl_three_vector_cross_product_double_small_time_test_vs_linasm
        tmpl_three_vector_cross_product_float_huge_time_test_vs_linasm
        tmpl_three_vector_cross_product_float_small_time_test_vs_linasm
        tmpl_three_vector_cross_with_double_huge_time_test_vs_linasm
        tmpl_three_vector_cross_with_double_small_time_test_vs_linasm
        tmpl_three_vector_cross_with_float_huge_time_test_vs_linasm
        tmpl_three_vector_cross_with_float_small_time_test_vs_linasm
        tmpl_three_vector_dot_product_double_huge_time_test_vs_linasm
        tmpl_three_vector_dot_product_double_small_time_test_vs_linasm
        tmpl_three_vector_dot_product_float_huge_time_test_vs_linasm
        tmpl_three_vector_dot_product_float_small_time_test_vs_linasm
        tmpl_three_vector_l2_norm_double_huge_time_test_vs_linasm
        tmpl_three_vector_l2_norm_double_small_time_test_vs_linasm
    )

    foreach(app ${linasm_test_apps})
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
    TARGETS ${test_apps} ${linasm_test_apps}
    RUNTIME
    DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
