cmake_minimum_required(VERSION 3.20)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../cmake")

include(FindBoost)

project(integer_time_tests)

find_package(Boost REQUIRED)

file(GLOB c_sources CONFIGURE_DEPENDS *.c)
file(GLOB cpp_sources CONFIGURE_DEPENDS *.cpp)
if(NOT "${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
    # Exclude tests that use GCC builtins when not compiling with GCC
    list(
        REMOVE_ITEM
        c_sources
        "${CMAKE_CURRENT_SOURCE_DIR}/tmpl_integer_leading_zeros_uchar_test.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/tmpl_integer_leading_zeros_uint_test.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/tmpl_integer_leading_zeros_ullong_test.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/tmpl_integer_leading_zeros_ulong_test.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/tmpl_integer_leading_zeros_ushort_test.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/tmpl_integer_trailing_zeros_char_test.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/tmpl_integer_trailing_zeros_int_test.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/tmpl_integer_trailing_zeros_long_test.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/tmpl_integer_trailing_zeros_short_test.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/tmpl_integer_trailing_zeros_uchar_test.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/tmpl_integer_trailing_zeros_uint_test.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/tmpl_integer_trailing_zeros_ulong_test.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/tmpl_integer_trailing_zeros_ushort_test.c"
    )
endif()

foreach(source ${c_sources})
    cmake_path(GET source STEM app)
    list(APPEND test_c_apps ${app})
    add_executable(${app} ${source})
    set_target_properties(
        ${app} PROPERTIES INTERPROCEDURAL_OPTIMIZATION ${IPO_SUPPORTED} )
    if(DEFINED CROSSCOMPILING_EMULATOR)
        set_target_properties(${app} PROPERTIES CROSSCOMPILING_EMULATOR ${CROSSCOMPILING_EMULATOR})
    endif()
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

foreach(source ${cpp_sources})
    cmake_path(GET source STEM app)
    list(APPEND test_cpp_apps ${app})
    add_executable(${app} ${source})
    set_target_properties(
        ${app} PROPERTIES INTERPROCEDURAL_OPTIMIZATION ${IPO_SUPPORTED} )
    if(DEFINED CROSSCOMPILING_EMULATOR)
        set_target_properties(${app} PROPERTIES CROSSCOMPILING_EMULATOR ${CROSSCOMPILING_EMULATOR})
    endif()
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
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
