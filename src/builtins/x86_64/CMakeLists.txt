target_sources(
    tmpl
    PRIVATE
        tmpl_cos_double_x86_64.S
        tmpl_cos_float_x86_64.S
        tmpl_cos_ldouble_x86_64.S
        tmpl_sin_double_x86_64.S
        tmpl_sin_float_x86_64.S
        tmpl_sin_ldouble_x86_64.S
        tmpl_sincos_double_x86_64.S
        tmpl_sincos_float_x86_64.S
        tmpl_sincos_ldouble_x86_64.S
)

list(
    APPEND
    SOURCE_EXCLUSION_LIST
    "tmpl_cos_double.c"
    "tmpl_cos_float.c"
    "tmpl_cos_ldouble.c"
    "tmpl_sin_double.c"
    "tmpl_sin_float.c"
    "tmpl_sin_ldouble.c"
    "tmpl_sincos_double.c"
    "tmpl_sincos_float.c"
    "tmpl_sincos_ldouble.c"
)
set(SOURCE_EXCLUSION_LIST ${SOURCE_EXCLUSION_LIST} PARENT_SCOPE)
