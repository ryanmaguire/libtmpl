set(sources tmpl_sorted_linear_interpolation.c)

list(REMOVE_ITEM sources ${SOURCE_EXCLUSION_LIST})

target_sources(tmpl PRIVATE ${sources})
