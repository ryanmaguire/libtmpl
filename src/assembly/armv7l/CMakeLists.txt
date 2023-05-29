target_sources(tmpl PRIVATE tmpl_sqrt_double_armv7l.S tmpl_sqrt_float_armv7l.S tmpl_sqrt_ldouble_armv7l.S)

list(APPEND SOURCE_EXCLUSION_LIST "tmpl_sqrt_double.c" "tmpl_sqrt_float.c" "tmpl_sqrt_ldouble.c")
set(SOURCE_EXCLUSION_LIST
    ${SOURCE_EXCLUSION_LIST}
    PARENT_SCOPE
)
