set(sources
    tmpl_create_svg_canvas.c
    tmpl_destroy_svg.c
    tmpl_destroy_svg_canvas.c
    tmpl_svg_colors.c
    tmpl_svg_set_arrow_pos.c
    tmpl_svg_set_arrow_size.c
    tmpl_svg_set_arrow_type.c
)

list(REMOVE_ITEM sources ${SOURCE_EXCLUSION_LIST})

target_sources(tmpl PRIVATE ${sources})
