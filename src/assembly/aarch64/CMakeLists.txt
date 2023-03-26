target_sources(
    tmpl
    PRIVATE
        tmpl_floor_double_aarch64.S
        tmpl_floor_float_aarch64.S
        tmpl_sqrt_double_aarch64.S
        tmpl_sqrt_float_aarch64.S
)

list(
    APPEND
    SOURCE_EXCLUSION_LIST
    "tmpl_floor_double.c"
    "tmpl_floor_float.c"
    "tmpl_sqrt_double.c"
    "tmpl_sqrt_float.c"
)
set(SOURCE_EXCLUSION_LIST ${SOURCE_EXCLUSION_LIST} PARENT_SCOPE)
