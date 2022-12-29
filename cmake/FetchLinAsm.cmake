include_guard()

if(NOT DEFINED LIBTMPL_LINASM_BRANCH)
    set(LIBTMPL_LINASM_BRANCH master)
endif()

if(NOT DEFINED LIBTMPL_LINASM_SRC)
    set(LIBTMP_LINASM_SRC ${CMAKE_CURRENT_BINARY_DIR}/src/linasm)
endif()

if(NOT EXISTS "${LIBTMPL_LINASM_SRC}")
    fetchcontent_declare(
        linasm-checkout
        GIT_REPOSITORY https://github.com/rurban/linasm.git
        GIT_TAG ${LIBTMPL_LINASM_BRANCH}
        SOURCE_DIR
        ${LIBTMP_LINASM_SRC}
        GIT_PROGRESS
        TRUE
    )

    fetchcontent_makeavailable(linasm-checkout)
endif()

set(linasm_INCLUDE_DIR "${LIBTMP_LINASM_SRC}/include")
set(linasm_SOURCE_DIR "${LIBTMP_LINASM_SRC}/source")
