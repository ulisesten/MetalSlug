cmake_minimum_required(VERSION 3.7)
project(metalSlug)

set(SRC
    src/main.cpp
    src/floor.cpp
    src/animation.cpp
    src/movement.cpp
)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
#include_directories(metalSlug ${SDL2_INCLUDE_DIRS})

add_executable( metalSlug ${SRC})

target_include_directories( metalSlug
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/assets
)

target_link_libraries(metalSlug SDL2::Main SDL2::Image)