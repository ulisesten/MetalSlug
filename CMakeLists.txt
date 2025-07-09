cmake_minimum_required(VERSION 3.10)
project(MetalSlugC C)

set(CMAKE_C_STANDARD 99)

# Ruta base del código fuente
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)

# SDL2 y SDL2_image
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIRS}
    ${SRC_DIR}
    ${SRC_DIR}/game
    ${SRC_DIR}/input
    ${SRC_DIR}/render
)

# Archivos fuente
file(GLOB GAME_SRC ${SRC_DIR}/game/*.c)
file(GLOB INPUT_SRC ${SRC_DIR}/input/*.c)
file(GLOB RENDER_SRC ${SRC_DIR}/render/*.c)

add_executable(metal_slug
    ${SRC_DIR}/main.c
    ${GAME_SRC}
    ${INPUT_SRC}
    ${RENDER_SRC}
)

target_link_libraries(metal_slug
    ${SDL2_LIBRARIES}
    SDL2_image
)