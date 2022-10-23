set(sources
    tmpl_five_point_derivative.c
    tmpl_halleys_method.c
    tmpl_halleys_method_complex.c
    tmpl_newton_raphson.c
    tmpl_newton_raphson_poly.c
    tmpl_newtons_method_complex.c
)
list(REMOVE_ITEM sources ${SOURCE_EXCLUSION_LIST})

target_sources(tmpl PRIVATE ${sources})
