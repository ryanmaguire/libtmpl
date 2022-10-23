set(sources
    tmpl_get_void_from_void_cd2cd.c
    tmpl_get_void_from_void_cf2cf.c
    tmpl_get_void_from_void_cld2cld.c
    tmpl_get_void_from_void_d2cd.c
    tmpl_get_void_from_void_d2d.c
    tmpl_get_void_from_void_f2cf.c
    tmpl_get_void_from_void_f2f.c
    tmpl_get_void_from_void_l2l.c
    tmpl_get_void_from_void_ld2cld.c
    tmpl_get_void_from_void_ld2ld.c
)

list(REMOVE_ITEM sources ${SOURCE_EXCLUSION_LIST})

target_sources(tmpl PRIVATE ${sources})
