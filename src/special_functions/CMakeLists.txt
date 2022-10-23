set(sources
    tmpl_bessel_I0_complexdouble.c
    tmpl_bessel_I0_double.c
    tmpl_bessel_I0_float.c
    tmpl_bessel_I0_ldouble.c
    tmpl_bessel_J0.c
    tmpl_bessel_J0_float.c
    tmpl_fresnel_cos_double.c
    tmpl_fresnel_cos_float.c
    tmpl_fresnel_cos_ldouble.c
    tmpl_fresnel_integral.c
    tmpl_fresnel_sin_double.c
    tmpl_fresnel_sin_float.c
    tmpl_fresnel_sin_ldouble.c
    tmpl_lambertw.c
    tmpl_legendre.c
    tmpl_where.c
)

list(REMOVE_ITEM sources ${SOURCE_EXCLUSION_LIST})

target_sources(tmpl PRIVATE ${sources})
