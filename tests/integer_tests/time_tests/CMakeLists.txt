cmake_minimum_required(VERSION 3.20)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../cmake")

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    if(APPLE)
        include(gcc-macos)
    elseif(UNIX)
        include(gcc)
    endif()
endif()

project(integer_time_tests)

set(test_apps
    tmpl_integer_abs_char_time_test
    tmpl_integer_abs_int_time_test
    tmpl_integer_abs_llong_time_test
    tmpl_integer_abs_long_time_test
    tmpl_integer_abs_short_time_test
    tmpl_integer_gcd_int
    tmpl_integer_gcd_uint
    tmpl_integer_gcd_ulong
    tmpl_integer_leading_zeros_uchar_test
    tmpl_integer_leading_zeros_uint_test
    tmpl_integer_leading_zeros_ulong_test
    tmpl_integer_leading_zeros_ushort_test
    tmpl_integer_trailing_zeros_char_test
    tmpl_integer_trailing_zeros_int_test
    tmpl_integer_trailing_zeros_long_test
    tmpl_integer_trailing_zeros_short_test
    tmpl_integer_trailing_zeros_uchar_test
    tmpl_integer_trailing_zeros_uint_test
    tmpl_integer_trailing_zeros_ulong_test
    tmpl_integer_trailing_zeros_ushort_test
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
