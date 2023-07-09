cmake_minimum_required(VERSION 3.20)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../cmake")

include(FindBoost)

project(rational_time_tests LANGUAGES C CXX)

find_package(Boost REQUIRED)

file(GLOB sources CONFIGURE_DEPENDS *.cpp)

foreach(source ${sources})
    cmake_path(GET source STEM app)
    list(APPEND test_apps ${app})
    add_executable(${app} ${source})
    set_target_properties(
        ${app} PROPERTIES INTERPROCEDURAL_OPTIMIZATION ${IPO_SUPPORTED} CROSSCOMPILING_EMULATOR
                                                                        ${CROSSCOMPILING_EMULATOR}
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

    add_test(NAME test_${app} COMMAND ${app})
endforeach()

include(GNUInstallDirs)
install(
    TARGETS ${test_apps}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
