include_guard()
include(FetchContent)

if(NOT DEFINED LIBTMPL_KISSVG_BRANCH)
    set(LIBTMPL_KISSVG_BRANCH master)
endif()

if(NOT DEFINED LIBTMPL_KISSVG_SRC)
    set(LIBTMPL_KISSVG_SRC ${CMAKE_CURRENT_BINARY_DIR}/src/kissvg)
endif()

if(NOT EXISTS "${LIBTMPL_KISSVG_SRC}")
    FetchContent_Declare(
        kissvg-checkout
        GIT_REPOSITORY https://github.com/ryanmaguire/kissvg.git
        GIT_TAG ${LIBTMPL_KISSVG_BRANCH}
        SOURCE_DIR ${LIBTMP_KISSVG_SRC}
        GIT_PROGRESS TRUE
    )

    FetchContent_MakeAvailable(kissvg-checkout)
endif()

set(LIBTMP)
