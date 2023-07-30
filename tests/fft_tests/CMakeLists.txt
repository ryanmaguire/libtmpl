cmake_minimum_required(VERSION 3.20)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../cmake")

if(LINUX)
    project(fft_time_tests)

    find_library(FFTW_LIB NAMES libfftw.a libfftw.so REQUIRED)

    find_file(FFTW_HEADER fftw.h PATHS /usr/include REQUIRED)
    cmake_path(GET FFTW_HEADER PARENT_PATH FFTW_INCLUDE_DIR)

    file(GLOB sources CONFIGURE_DEPENDS *.c)

    foreach(source ${sources})
        cmake_path(GET source STEM app)
        list(APPEND test_apps ${app})
        add_executable(${app} ${source})
        set_target_properties(${app} PROPERTIES INTERPROCEDURAL_OPTIMIZATION ${IPO_SUPPORTED} C_STANDARD 11)
        if(DEFINED CROSSCOMPILING_EMULATOR)
            set_target_properties(${app} PROPERTIES CROSSCOMPILING_EMULATOR ${CROSSCOMPILING_EMULATOR})
        endif()
        target_include_directories(${app} PUBLIC "${TMPL_PARENT_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}" "${FFTW_INCLUDE_DIR}")
        target_link_libraries(${app} PRIVATE "${FFTW_LIB}" tmpl::tmpl m)

        add_test(NAME test_${app} COMMAND ${app})
    endforeach()

    include(GNUInstallDirs)
    install(
        TARGETS ${test_apps}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )

endif()
