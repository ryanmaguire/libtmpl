target_sources(
    tmpl
    PRIVATE
        tmpl_floor_double_i386.S
        tmpl_floor_float_i386.S
        tmpl_floor_ldouble_i386.S
        tmpl_sqrt_double_i386.S
        tmpl_sqrt_float_i386.S
        tmpl_sqrt_ldouble_i386.S
        tmpl_trailing_zeros_char_i386.S
        tmpl_trailing_zeros_int_i386.S
        tmpl_trailing_zeros_long_i386.S
        tmpl_trailing_zeros_short_i386.S
        tmpl_trailing_zeros_uchar_i386.S
        tmpl_trailing_zeros_uint_i386.S
        tmpl_trailing_zeros_ulong_i386.S
        tmpl_trailing_zeros_ushort_i386.S
)

#TODO do we need to install the header with our header file set?
target_include_directories(tmpl PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

list(
    APPEND
    SOURCE_EXCLUSION_LIST
    "tmpl_trailing_zeros_char.c"
    "tmpl_trailing_zeros_int.c"
    "tmpl_trailing_zeros_long.c"
    "tmpl_trailing_zeros_short.c"
    "tmpl_trailing_zeros_uint.c"
    "tmpl_trailing_zeros_uchar.c"
    "tmpl_trailing_zeros_ulong.c"
    "tmpl_trailing_zeros_ushort.c"
    "tmpl_sqrt_double.c"
    "tmpl_sqrt_float.c"
    "tmpl_sqrt_ldouble.c"
    "tmpl_floor_double.c"
    "tmpl_floor_float.c"
    "tmpl_floor_ldouble.c"
)

set(SOURCE_EXCLUSION_LIST ${SOURCE_EXCLUSION_LIST} PARENT_SCOPE)
