cmake_minimum_required(VERSION 3.20)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../cmake")

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    if(APPLE)
        include(gcc-macos)
    elseif(UNIX)
        include(gcc)
    endif()
endif()

project(special_function_time_tests)
include(FindGSL)
set(test_apps
    tmpl_bessel_j0_double_small_time_test_vs_gsl
    tmpl_bessel_j0_double_time_test
    tmpl_bessel_j0_ldouble_time_test
)

foreach(app ${test_apps})
    add_executable(${app} ${app}.c)
    set_target_properties(${app} PROPERTIES INTERPROCEDURAL_OPTIMIZATION ${IPO_SUPPORTED})
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

include(GNUInstallDirs)
install(TARGETS ${test_apps} RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
