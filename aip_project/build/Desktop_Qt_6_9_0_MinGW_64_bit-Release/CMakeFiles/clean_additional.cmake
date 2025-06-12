# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles\\aip_project_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\aip_project_autogen.dir\\ParseCache.txt"
  "CMakeFiles\\sqlite3_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\sqlite3_autogen.dir\\ParseCache.txt"
  "aip_project_autogen"
  "sqlite3_autogen"
  )
endif()
