cmake_minimum_required(VERSION 3.10)
project(MetalSlugC C)

set(CMAKE_C_STANDARD 99)

# Ruta base del código fuente
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)

## Windows config
if(WIN32)
    set(SDL2_DIR "${CMAKE_SOURCE_DIR}/libs/SDL2/x86_64-w64-mingw32")
    include_directories(${SDL2_DIR}/include)
    link_directories(${SDL2_DIR}/lib)
else()
    # SDL2 y SDL2_image
    find_package(SDL2 REQUIRED)
    find_package(SDL2_image REQUIRED)
endif()



include_directories(
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIRS}
    ${SRC_DIR}
    ${SRC_DIR}/game
    ${SRC_DIR}/input
    ${SRC_DIR}/render
    ${SRC_DIR}/animation
)

# Archivos fuente
file(GLOB GAME_SRC ${SRC_DIR}/game/*.c)
file(GLOB INPUT_SRC ${SRC_DIR}/input/*.c)
file(GLOB RENDER_SRC ${SRC_DIR}/render/*.c)
file(GLOB ANIMATION_SRC ${SRC_DIR}/animation/*.c)

add_executable(metal_slug
    ${SRC_DIR}/main.c
    ${GAME_SRC}
    ${INPUT_SRC}
    ${RENDER_SRC}
    ${ANIMATION_SRC}
)

if(WIN32)
    if(MSVC) # Para compilador Visual Studio
        target_link_libraries(metal_slug SDL2 SDL2main SDL2_image)
    else()
        target_link_libraries(metal_slug SDL2 SDL2main SDL2_image mingw32) # Para MinGW
    endif()
else()
    target_link_libraries(metal_slug
        ${SDL2_LIBRARIES}
        SDL2_image
    )
endif()


if(WIN32)
    # Copiar las librerías DLL al directorio de construcción
    add_custom_command(TARGET metal_slug POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/libs/SDL2/x86_64-w64-mingw32/bin"
        $<TARGET_FILE_DIR:metal_slug>
    COMMENT "Copiando DLLs de SDL2 al directorio de salida"
    )
endif()