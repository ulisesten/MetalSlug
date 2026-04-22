#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef struct {
    SDL_Surface *scenario, *player, *player_back, *soldier;
    SDL_Texture *sco_texture, *pla_texture, *pla_texture_back;
} GameAssets;
void startGame(SDL_Renderer* renderer, SDL_Window* window);

#endif