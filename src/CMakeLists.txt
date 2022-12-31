file(GLOB_RECURSE sources CONFIGURE_DEPENDS *.c)

list(REMOVE_ITEM sources ${SOURCE_EXCLUSION_LIST})

target_sources(tmpl PRIVATE ${sources})
