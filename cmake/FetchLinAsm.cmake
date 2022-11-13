include_guard()

if(NOT DEFINED LIBTMPL_LINASM_BRANCH)
    set(LIBTMPL_LINASM_BRANCH master)
endif()

fetchcontent_declare(
    linasm-checkout
    GIT_REPOSITORY https://github.com/rurban/linasm.git
    GIT_TAG ${LIBTMPL_LINASM_BRANCH}
    SOURCE_DIR
    GIT_PROGRESS
    TRUE
)

fetchcontent_makeavailable(linasm-checkout)

set(linasm_INCLUDE_DIR "${linasm_checkout_SOURCE_DIR}/include")
set(linasm_SOURCE_DIR "${linasm_checkout_SOURCE_DIR}/source")
