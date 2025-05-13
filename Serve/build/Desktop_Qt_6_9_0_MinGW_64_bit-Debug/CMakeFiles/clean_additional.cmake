# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Serve_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Serve_autogen.dir\\ParseCache.txt"
  "Serve_autogen"
  )
endif()
