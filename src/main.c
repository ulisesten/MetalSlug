#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "game/game.h"
//#include "menu/menu.h"

int main(int argc, char** argv) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0) {
        printf("Error SDL_Init: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        printf("Error IMG_Init: %s\n", IMG_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    SDL_Window* window = SDL_CreateWindow("Metal Slug", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 502, 238, SDL_WINDOW_OPENGL);
    if (!window) {
        printf("Error SDL_CreateWindow: %s\n", SDL_GetError());
        IMG_Quit();
        SDL_Quit();
        return EXIT_FAILURE;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(!renderer) {
        printf("no renderer %s\n", SDL_GetError());
    }

    // menuPersonaje(screen, window); // Activar si se quiere el menú
    startGame(renderer, window);       // Lógica del nivel 1

    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    return EXIT_SUCCESS;
}
