set(sources
    tmpl_are_gauss_tuples_identical.c
    tmpl_are_virtual_knots_identical.c
    tmpl_compute_knot_arcs.c
    tmpl_delete_virtual_knot_crossing.c
    tmpl_destroy_crossing_indices.c
    tmpl_destroy_gauss_tuple_pointer.c
    tmpl_destroy_virtual_knot_pointer.c
    tmpl_find_crossing_indices.c
    tmpl_gauss_code_from_string.c
    tmpl_is_gauss_code_valid.c
    tmpl_print_gauss_code.c
    tmpl_reidemeister_one_reduction.c
    tmpl_virtual_knot_genus.c
)

list(REMOVE_ITEM sources ${SOURCE_EXCLUSION_LIST})

target_sources(tmpl PRIVATE ${sources})
