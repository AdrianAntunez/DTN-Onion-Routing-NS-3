aux_source_directory(. parser_source_files)
set(parser_source_files ${parser_source_files} parser.h )
add_library(parsers ${parser_source_files})
target_link_libraries(parsers graph)

