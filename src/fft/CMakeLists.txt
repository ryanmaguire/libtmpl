set(sources
    tmpl_bluestein_chirp_z.c
    tmpl_complex_cooley_tukey_fft.c
    tmpl_complex_fft.c
)

list(REMOVE_ITEM sources ${SOURCE_EXCLUSION_LIST})

target_sources(tmpl PRIVATE ${sources})
