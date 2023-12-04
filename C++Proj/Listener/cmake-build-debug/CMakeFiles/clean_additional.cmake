# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Listener_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Listener_autogen.dir\\ParseCache.txt"
  "Listener_autogen"
  )
endif()
