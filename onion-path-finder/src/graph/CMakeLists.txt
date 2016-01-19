aux_source_directory(. graph_source_files)
add_library(graph ${graph_source_files})
target_link_libraries(graph)