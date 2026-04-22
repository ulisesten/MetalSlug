// Initialization header for moved functions
#ifndef INIT_H
#define INIT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "../render/floor.h"
#include "../animation/animation.h"
#include "../animation/animation_enemies.h"
#include "../input/input.h"
#include "../game/game.h"



void loadResources(GameAssets* assets, EnemyMatrix* matrix, FloorCoors* floor_coors);
void initPlayer(PlayerState* state, GameAssets assets, SDL_Renderer** renderer);
void initEnemies(EnemyState** ene_states, EnemyMatrix* matrix, GameAssets assets, SDL_Renderer** renderer);
void initScenario(ScenarioState* state, GameAssets assets, SDL_Renderer** renderer);

#endif // INIT_H
