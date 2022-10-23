set(sources
    tmpl_determine_endianness.c
    tmpl_swap_bytes.c
    tmpl_swap_most_significant_bit_2.c
    tmpl_swap_most_significant_bit_4.c
    tmpl_swap_most_significant_bit_8.c
)

list(REMOVE_ITEM sources ${SOURCE_EXCLUSION_LIST})

target_sources(tmpl PRIVATE ${sources})
