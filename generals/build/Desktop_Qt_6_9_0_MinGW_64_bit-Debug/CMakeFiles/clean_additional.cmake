# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\generals_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\generals_autogen.dir\\ParseCache.txt"
  "generals_autogen"
  )
endif()
