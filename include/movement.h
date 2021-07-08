#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <SDL2/SDL.h>
#include "util.h"

void handleEvents(SDL_Window* window, Events* events, Indices* i, int hight);
void ToggleFullscreen(SDL_Window* Window);

#endif