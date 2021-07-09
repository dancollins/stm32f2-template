# Sets up a compile-time define with each source file relative to the project
# root directory (as opposed to the absolute file path in __FILE__).
function(logging_set_filename target)
  get_target_property(sources "${target}" SOURCES)
  foreach(src ${sources})
    string(REPLACE "${CMAKE_SOURCE_DIR}" "" logging_file "${src}")
    set_property(SOURCE "${src}" APPEND PROPERTY
      COMPILE_DEFINITIONS "LOGGING_FILE=\"${logging_file}\"")
  endforeach()
endfunction()


# Wrapper to keep our namespace going
function(logging_set_default_level target level)
  target_compile_definitions("${target}" PRIVATE
    "-DLOG_LEVEL_DEFAULT=LOG_LEVEL_${level}")
endfunction()


# Helper for setting a given log level per-file
function(logging_set_level level sources)
  foreach(src ${sources})
    set_property(SOURCE "${src}" APPEND PROPERTY
      COMPILE_DEFINITIONS "LOGGING_LEVEL=LOG_LEVEL_${level}")
  endforeach()
endfunction()
