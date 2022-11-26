cmake_minimum_required(VERSION 3.20)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../cmake")

project(integer_time_tests)
include(FindBoost)
find_package(Boost REQUIRED)

set(test_c_apps
    tmpl_integer_abs_char_time_test
    tmpl_integer_abs_int_time_test
    tmpl_integer_abs_llong_time_test
    tmpl_integer_abs_long_time_test
    tmpl_integer_abs_short_time_test
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

foreach(app ${test_c_apps})
    add_executable(${app} ${app}.c)
    set_target_properties(
        ${app}
        PROPERTIES INTERPROCEDURAL_OPTIMIZATION ${IPO_SUPPORTED}
    )
    target_include_directories(
        ${app}
        PUBLIC "${TMPL_PARENT_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}"
        PRIVATE "${Boost_INCLUDE_DIR}" "${Boost_INCLUDE_DIR}/boost"
    )
    target_link_libraries(${app} PRIVATE tmpl::tmpl)
    if(UNIX)
        target_link_libraries(${app} PRIVATE m)
    endif()
endforeach()

set(test_cpp_apps
    tmpl_integer_gcd_int
    tmpl_integer_gcd_uint
    tmpl_integer_gcd_ulong
)

foreach(app ${test_cpp_apps})
    add_executable(${app} ${app}.cpp)
    set_target_properties(
        ${app}
        PROPERTIES INTERPROCEDURAL_OPTIMIZATION ${IPO_SUPPORTED}
    )
    target_include_directories(
        ${app}
        PUBLIC "${TMPL_PARENT_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}"
        PRIVATE "${Boost_INCLUDE_DIR}" "${Boost_INCLUDE_DIR}/boost"
    )
    target_link_libraries(${app} PRIVATE tmpl::tmpl)
    if(UNIX)
        target_link_libraries(${app} PRIVATE m)
    endif()
endforeach()

include(GNUInstallDirs)
install(
    TARGETS ${test_c_apps} ${test_cpp_apps}
    RUNTIME
    DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
