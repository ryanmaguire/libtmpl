set(sources
    tmpl_inverse_orthographic_projection.c
    tmpl_inverse_orthographic_projection_torus.c
    tmpl_stereographic_projection.c
    tmpl_stereographic_projection_torus.c
)

list(REMOVE_ITEM sources ${SOURCE_EXCLUSION_LIST})

target_sources(tmpl PRIVATE ${sources})
