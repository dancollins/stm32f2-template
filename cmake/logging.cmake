# Copyright 2021 Dan Collins
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

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
