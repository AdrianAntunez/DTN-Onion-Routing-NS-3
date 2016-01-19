aux_source_directory(. ui_source_files)
add_library(ui ${ui_source_files})
target_link_libraries(ui)
