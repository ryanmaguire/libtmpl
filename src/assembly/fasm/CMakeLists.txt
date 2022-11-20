target_sources(tmpl PRIVATE tmpl_sqrt_x86_64.fasm)

list(APPEND SOURCE_EXCLUSION_LIST "tmpl_sqrt_double.c" "tmpl_sqrt_float.c")
set(SOURCE_EXCLUSION_LIST ${SOURCE_EXCLUSION_LIST} PARENT_SCOPE)
