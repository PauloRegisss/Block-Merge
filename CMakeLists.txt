cmake_minimum_required(VERSION 3.22)

project(BlockBlast
    VERSION 1.0.0
    DESCRIPTION "A 2D block puzzle game built with C and raylib"
    LANGUAGES C
)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

find_package(raylib 5.5 QUIET)

if(NOT raylib_FOUND)
    include(FetchContent)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 5.5
        GIT_SHALLOW TRUE
    )
    FetchContent_MakeAvailable(raylib)
endif()

set(PROJECT_SOURCES
    src/main.c
    src/game.c
    src/board.c
    src/piece.c
    src/screens/fonts/fonts.c
    src/screens/menu/menu.c
)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/src/screens
        ${CMAKE_CURRENT_SOURCE_DIR}/src/screens/fonts
        ${CMAKE_CURRENT_SOURCE_DIR}/src/screens/menu
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        raylib
)

if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(${PROJECT_NAME}
        PRIVATE
            -Wall
            -Wextra
            -Wpedantic
            -Wconversion
            -Wshadow
    )
endif()