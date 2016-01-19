aux_source_directory(. utils_source_files)
add_library(utils ${utils_source_files})
target_link_libraries(utils graph)

