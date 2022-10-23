set(sources
    tmpl_ascii_lower_case.c
    tmpl_ascii_upper_case.c
    tmpl_lower_case.c
    tmpl_make_lower.c
    tmpl_remove_spaces.c
    tmpl_strdup.c
    tmpl_upper_case.c
)

list(REMOVE_ITEM sources ${SOURCE_EXCLUSION_LIST})

target_sources(tmpl PRIVATE ${sources})
