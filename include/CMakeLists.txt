include(GenerateExportHeader)
generate_export_header(
    tmpl # generates the export header shared_EXPORTS.h automatically
    BASE_NAME
    tmpl
    EXPORT_MACRO_NAME
    TMPL_EXPORT
    EXPORT_FILE_NAME
    tmpl_exports.h
    STATIC_DEFINE
    SHARED_EXPORTS_BUILT_AS_STATIC
)

include(headerList)

target_sources(
    tmpl
    PUBLIC FILE_SET
           HEADERS
           FILES
           ${CMAKE_CURRENT_BINARY_DIR}/tmpl_exports.h
           ${CMAKE_CURRENT_BINARY_DIR}/tmpl_config.h
           ${CMAKE_CURRENT_BINARY_DIR}/tmpl_inttype.h
           ${CMAKE_CURRENT_BINARY_DIR}/tmpl_limits.h
)
