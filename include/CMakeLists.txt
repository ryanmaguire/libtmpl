include(GenerateExportHeader)
generate_export_header(
    tmpl # generates the export header shared_EXPORTS.h automatically
    BASE_NAME tmpl
    EXPORT_MACRO_NAME TMPL_EXPORT
    EXPORT_FILE_NAME tmpl_exports.h
    STATIC_DEFINE SHARED_EXPORTS_BUILT_AS_STATIC
)

target_sources(
    tmpl
    PUBLIC
        FILE_SET HEADERS
        FILES
            tmpl.h
            tmpl_bool.h
            tmpl_bytes.h
            tmpl_complex.h
            tmpl_fft.h
            tmpl_graph_theory.h
            tmpl_integer.h
            tmpl_interpolate.h
            tmpl_inversive_geometry.h
            tmpl_knots.h
            tmpl_math.h
            tmpl_matrix.h
            tmpl_numerical.h
            tmpl_optics.h
            tmpl_polynomial.h
            tmpl_ppm.h
            tmpl_quadruple.h
            tmpl_rational.h
            tmpl_sort.h
            tmpl_special_functions.h
            tmpl_spherical_geometry.h
            tmpl_string.h
            tmpl_svg.h
            tmpl_vec2.h
            tmpl_vec3.h
            tmpl_vector_complex.h
            tmpl_vector_integer.h
            tmpl_vector_real.h
            tmpl_void_pointer.h
            tmpl_window_functions.h
            ${CMAKE_CURRENT_BINARY_DIR}/tmpl_exports.h
            ${CMAKE_CURRENT_BINARY_DIR}/tmpl_config.h
            ${CMAKE_CURRENT_BINARY_DIR}/tmpl_inttype.h
)

add_subdirectory("complex")
add_subdirectory("integer")
add_subdirectory("math")
