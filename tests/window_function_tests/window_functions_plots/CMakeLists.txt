cmake_minimum_required(VERSION 3.20)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../cmake")

include(FindGSL)

project(windows_functions_plot_tests)

file(GLOB sources CONFIGURE_DEPENDS *.c)

foreach(source ${sources})
    cmake_path(GET source STEM app)
    list(APPEND test_apps ${app})
    add_executable(${app} ${source})
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
install(
    TARGETS ${test_apps}
    RUNTIME
    DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
