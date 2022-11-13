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
    tmpl_abs_double_example
    tmpl_abs_float_example
    tmpl_abs_ldouble_example
    tmpl_arctan_double_example
    tmpl_arctan_float_example
    tmpl_arctan_ldouble_example
    tmpl_infinity_example
    tmpl_is_inf_double_example
    tmpl_is_inf_float_example
    tmpl_is_inf_ldouble_example
    tmpl_is_nan_double_example
    tmpl_is_nan_float_example
    tmpl_is_nan_ldouble_example
    tmpl_is_nan_or_inf_double_example
    tmpl_nan_example
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
