#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef struct {
    SDL_Surface *scenarioSurface, *playerSurface, *playerBackSurface, *soldierSurface;
} GameAssets;
void startGame(SDL_Renderer* renderer, SDL_Window* window);

#endif