cmake_minimum_required(VERSION 3.20)
list(APPEND CMAKE_MODULE_PATH "${TMPL_PARENT_DIR}/cmake")

project(ppm_newton_fractals_examples)

file(GLOB sources CONFIGURE_DEPENDS *.c)

foreach(source ${sources})
    cmake_path(GET source STEM app)
    list(APPEND test_apps ${app})
    add_executable(${app} ${source})
    set_target_properties(${app} PROPERTIES INTERPROCEDURAL_OPTIMIZATION ${IPO_SUPPORTED})
    target_include_directories(${app} PUBLIC "${TMPL_PARENT_DIR}")
    target_link_libraries(${app} PRIVATE tmpl::tmpl)
    if(UNIX)
        target_link_libraries(${app} PRIVATE m)
    endif()
endforeach()

include(GNUInstallDirs)
install(
    TARGETS ${test_apps}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
