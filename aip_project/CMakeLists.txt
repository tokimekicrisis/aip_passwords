cmake_minimum_required(VERSION 3.10)
project(AIP_PROJECT VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_SOURCE_DIR}/ui)
set(CMAKE_AUTOUIC_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/generated_ui)

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

set(UI_FILES
    ${CMAKE_SOURCE_DIR}/ui/main_window.ui
    ${CMAKE_SOURCE_DIR}/ui/edit_pw.ui
    ${CMAKE_SOURCE_DIR}/ui/delete.ui
    ${CMAKE_SOURCE_DIR}/ui/pw_dialog.ui
)

add_executable(aip_project
    src/main.cpp
    src/database.cpp
    src/main_window.cpp
    src/pw_dialog.cpp
    include/database/database.h
    include/ui/main_window.h
    include/ui/table_model.h
    include/ui/pw_dialog.h
    ${UI_FILES}
)

target_include_directories(aip_project PRIVATE
    ${CMAKE_BINARY_DIR}/generated_ui
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

option(BUILD_TESTING "Build the testing tree" ON)

if(BUILD_TESTING)
    include(FetchContent)
    FetchContent_Declare(
        doctest
        GIT_REPOSITORY https://github.com/doctest/doctest.git
        GIT_TAG v2.4.11
    )
    FetchContent_MakeAvailable(doctest)

    add_executable(aip_tests
        tests/database_tests.cpp
        src/database.cpp
    )

    target_include_directories(aip_tests PRIVATE
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/include/database
        ${CMAKE_BINARY_DIR}/generated_ui
    )

    target_link_libraries(aip_tests PRIVATE
        sqlite3
        Qt6::Widgets
        doctest::doctest
    )
    enable_testing()
    add_test(NAME aip_tests COMMAND aip_tests)
endif()
