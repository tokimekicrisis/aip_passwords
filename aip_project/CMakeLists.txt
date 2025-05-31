cmake_minimum_required(VERSION 3.10)
project(AIP_PROJECT)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(
    ${CMAKE_SOURCE_DIR}/include/database
    ${CMAKE_SOURCE_DIR}/include
)

if(WIN32)
    add_library(sqlite3 STATIC ${CMAKE_SOURCE_DIR}/src/sqlite3.c)
    target_compile_definitions(sqlite3 PRIVATE SQLITE_ENABLE_COLUMN_METADATA)
  
else()
    find_package(SQLite3 REQUIRED)
    if(NOT SQLite3_FOUND)
        message(FATAL_ERROR "SQLite3 not found")
    endif()
endif()

add_executable(aip_project
    src/main.cpp
    src/database.cpp
)

if(WIN32)
    target_link_libraries(aip_project PRIVATE sqlite3)
else()
    target_link_libraries(aip_project PRIVATE ${SQLite3_LIBRARIES})
endif()