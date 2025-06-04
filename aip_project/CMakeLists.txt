cmake_minimum_required(VERSION 3.10)
project(AIP_PROJECT VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_AUTOUIC ON)

if(NOT DEFINED QT_PATH)
    set(QT_PATH "C:/Qt/6.9.0/mingw_64" CACHE PATH "Path to Qt installation")
endif()
list(APPEND CMAKE_PREFIX_PATH ${QT_PATH})

find_package(Qt6 REQUIRED COMPONENTS Widgets)
if(NOT Qt6_FOUND)
    message(FATAL_ERROR "Qt6 not found. Please set QT_PATH or CMAKE_PREFIX_PATH")
endif()

add_library(sqlite3 STATIC ${CMAKE_SOURCE_DIR}/src/sqlite3.c)
set_target_properties(sqlite3 PROPERTIES LINKER_LANGUAGE C)
target_compile_definitions(sqlite3 PRIVATE
    SQLITE_ENABLE_COLUMN_METADATA
    SQLITE_ENABLE_FTS5
)

add_executable(aip_project
    src/main.cpp
    src/database.cpp
    ui/aip_ui.ui
)

target_include_directories(aip_project PRIVATE
    ${CMAKE_SOURCE_DIR}/include/database
    ${CMAKE_SOURCE_DIR}/include
    ${Qt6Widgets_INCLUDE_DIRS}
)

target_link_libraries(aip_project PRIVATE
    sqlite3
    Qt6::Widgets
)

if(WIN32 AND EXISTS "${CMAKE_SOURCE_DIR}/include/lib/sqlite3.dll")
    add_custom_command(TARGET aip_project POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_SOURCE_DIR}/include/lib/sqlite3.dll"
        $<TARGET_FILE_DIR:aip_project>
    )
endif()
