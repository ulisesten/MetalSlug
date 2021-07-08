#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include <stdbool.h>

#include "util.h"

void player(int x, int y, int action, bool direction, struct SdlConfig config);

#endif