set(sources
    tmpl_polynomial_calloc.c
    tmpl_polynomial_create_empty.c
    tmpl_polynomial_destroy.c
    tmpl_polynomial_scale_self.c
)

list(REMOVE_ITEM sources ${SOURCE_EXCLUSION_LIST})

target_sources(tmpl PRIVATE ${sources})
