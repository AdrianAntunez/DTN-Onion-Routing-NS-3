aux_source_directory(. core_source_files)
set(core_source_files ${core_source_files} onion-constants.h )
add_library(core ${core_source_files})
target_link_libraries(core) 
