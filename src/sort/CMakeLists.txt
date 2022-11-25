set(sources
    tmpl_merge_sort_double.c
    tmpl_merge_sort_float.c
    tmpl_merge_sort_ldouble.c
)

list(REMOVE_ITEM sources ${SOURCE_EXCLUSION_LIST})

target_sources(tmpl PRIVATE ${sources})
