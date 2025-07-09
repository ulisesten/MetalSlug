#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "../render/animation.h"

/* typedef struct PlayerState PlayerState; */

void handleEvents(PlayerState* state);

#endif