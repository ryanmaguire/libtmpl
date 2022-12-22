cmake_minimum_required(VERSION 3.20)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../cmake")

include(FindGSL)

project(sort_unit_tests LANGUAGES C CXX)

set(test_apps
    tmpl_merge_sort_double_unit_test_002
    tmpl_merge_sort_double_unit_test_003
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

set(cpp_test_apps
    tmpl_merge_sort_double_unit_test_001
    tmpl_merge_sort_double_unit_test_004
)

foreach(app ${cpp_test_apps})
    add_executable(${app} ${app}.cpp)
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
    TARGETS ${test_apps} ${cpp_test_apps}
    RUNTIME
    DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
