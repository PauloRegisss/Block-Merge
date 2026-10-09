cmake_minimum_required(VERSION 3.22)

project(BlockBlast
    VERSION 1.0.0
    DESCRIPTION "A 2D block puzzle game built with C and raylib"
    LANGUAGES C
)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

find_package(raylib CONFIG REQUIRED)

add_executable(${PROJECT_NAME}
    src/main.c
    src/game.c
    src/board.c
    src/piece.c
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
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
