cmake_minimum_required(VERSION 2.8)
project(metalSlug)

set(CMAKE_BUILD_TYPE Debug)

add_subdirectory(${PROJECT_SOURCE_DIR}/modules/socket.io-client-cpp)


set(SRC
        ${PROJECT_SOURCE_DIR}/src/main.c
        ${PROJECT_SOURCE_DIR}/src/util.c
        ${PROJECT_SOURCE_DIR}/src/animation.c
        ${PROJECT_SOURCE_DIR}/src/movement.c
        ${PROJECT_SOURCE_DIR}/src/character_selection.c
        ${PROJECT_SOURCE_DIR}/src/main_loop.c
        ${PROJECT_SOURCE_DIR}/src/player.c
)

#list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

find_package(SDL2 REQUIRED)
#find_package(SDL2_image REQUIRED)
#include_directories(metalSlug ${SDL2_INCLUDE_DIRS})

add_executable( metalSlug ${SRC})

target_include_directories( metalSlug
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/assets
)

include_directories(/usr/include/)
link_directories(/usr/lib/x86_64-linux-gnu/)
find_library(NAMES SDL2_image PATHS /usr/lib/x86_64-linux-gnu/)

#target_link_libraries(metalSlug SDL2::Main SDL2::Image)
target_link_libraries(metalSlug SDL2 SDL2_image)