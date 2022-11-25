cmake_minimum_required(VERSION 3.20)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../cmake")

if(UNIX)
    project(bytes_tests)

    set(test_apps
        kissvg_ApolloniusGasket
        kissvg_ApolloniusGasketFordCircles
        kissvg_ApolloniusGasketFordCirclesSetup
        kissvg_ApolloniusGasketSetup
        kissvg_ApolloniusGasketStart
        kissvg_ApolloniusProblem
        kissvg_CircleFromThreePointsProblem
        kissvg_ColorTest
        kissvg_EuclidBookOnePropOne
        kissvg_sine
        kissvg_TestCircleError
        kissvg_TestInversiveGeometry
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
endif()
