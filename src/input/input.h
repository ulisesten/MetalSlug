#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "../animation/animation_player_clark.h"

/* typedef struct PlayerState PlayerState; */

void handleEvents(PlayerState* state);

#endif