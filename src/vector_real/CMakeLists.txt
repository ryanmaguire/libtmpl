set(sources
    tmpl_add_real_vector.c
    tmpl_create_empty_real_vector.c
    tmpl_create_vector_from_real_data.c
    tmpl_create_zero_real_vector.c
    tmpl_destroy_real_vector.c
)

list(REMOVE_ITEM sources ${SOURCE_EXCLUSION_LIST})

target_sources(tmpl PRIVATE ${sources})
