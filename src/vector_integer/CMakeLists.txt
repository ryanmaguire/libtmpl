set(sources
    tmpl_binary_gcd_uintvector.c
    tmpl_create_empty_char_vector.c
    tmpl_create_empty_int_vector.c
    tmpl_create_empty_long_vector.c
    tmpl_create_empty_short_vector.c
    tmpl_create_vector_from_char_data.c
    tmpl_create_vector_from_int_data.c
    tmpl_create_vector_from_long_data.c
    tmpl_create_vector_from_short_data.c
    tmpl_create_zero_char_vector.c
    tmpl_create_zero_int_vector.c
    tmpl_create_zero_long_vector.c
    tmpl_create_zero_short_vector.c
    tmpl_destroy_char_vector.c
    tmpl_destroy_int_vector.c
    tmpl_destroy_long_vector.c
    tmpl_destroy_short_vector.c
    tmpl_sieve_of_eratosthenes.c
)

list(REMOVE_ITEM sources ${SOURCE_EXCLUSION_LIST})

target_sources(tmpl PRIVATE ${sources})
