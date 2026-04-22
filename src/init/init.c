

#include "init.h"
#include "../game/game.h"
#include "../render/floor.h"
#include "../animation/animation.h"
#include "../animation/animation_enemies.h"
#include "../input/input.h"
#include "../utils/utils.h"
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

// ========================= Inicialización ==========================

void loadResources(GameAssets* assets, EnemyMatrix* matrix, FloorCoors* floor_coors) {
	assets->scenario = IMG_Load("src/resources/backgrounds/fondo_mision_1.png");
	assets->player = IMG_Load("src/resources/players/clark.png");
	assets->player_back = IMG_Load("src/resources/players/clarkBack.png");
	assets->soldier = IMG_Load("src/resources/enemies/soldier_enemy.png");

	//(*matrix) = malloc(sizeof(EnemyMatrix));
	matrix->matrix = readEnemyMatrix("src/resources/matrix/stage_1/enemies.txt", &matrix->count);
	floor_coors->coors = readFloorCoords("src/resources/coors/scene1-ground.txt", &floor_coors->count);

	if (!assets->scenario || !assets->player || !assets->player_back || !assets->soldier) {
		printf("Error cargando recursos: %s\n", IMG_GetError());
		exit(EXIT_FAILURE);
	}
}

void initPlayer(PlayerState* state, GameAssets assets, SDL_Renderer** renderer) {
	AnimationArrays* ani_arrays = malloc(sizeof(AnimationArrays));
	initAnimations(ani_arrays);

	*state = (PlayerState){
		.x = 0, .y = 0, .h = 25, .fullscreen = false,
		.iTorso = 0, .iPierna = 0, .iShoot = 0,
		.X_RANGE_MIN = 20, .X_RANGE_MAX = 400,
		.direction = DIRECTION_RIGHT, .directionAux = DIRECTION_RIGHT,
		.indexes = {4, 1},
		.animation_arrays = ani_arrays,
		.pla_texture        = SDL_CreateTextureFromSurface(*renderer, assets.player),
		.pla_texture_back   = SDL_CreateTextureFromSurface(*renderer, assets.player_back)
	};
}

void initEnemies(EnemyState** ene_states, EnemyMatrix* matrix, GameAssets assets, SDL_Renderer** renderer) {
	AnimationEnemyArrays* arrays = malloc(sizeof(AnimationEnemyArrays));
	initEnemyAnimations(arrays);

	SDL_Texture* _ene_texture = SDL_CreateTextureFromSurface(*renderer, assets.soldier);

	*ene_states = malloc(sizeof(EnemyState*) * (matrix->count));

	for (int i = 0; i < matrix->count; i++) {
		ene_states[i] = malloc(sizeof(EnemyState));
		*ene_states[i] = (EnemyState){
			.id = i,
			.x = matrix->matrix[i].x,
			.h = matrix->matrix[i].y,
			.y_offset = 24,
			.sco_offset = 0,
			.type = matrix->matrix[i].type,
			.mode = matrix->matrix[i].mode,
			.direction = DIRECTION_LEFT,
			.ani_arrays = arrays,
			.free_animation = true,
			.ene_texture = _ene_texture
		};
	}
}

void initScenario(ScenarioState* state, GameAssets assets, SDL_Renderer** renderer) {
	*state = (ScenarioState){
		.x = 0,
		.y = 10,
		.w = 555,
		.X_MOUNTAIN_OFFSET = 4,
		.X_HORIZON_OFFSET = 18,
		.X_SCO_OFFSET = 80,
		.MAX_WIDTH = 3320,
		.sco_texture = SDL_CreateTextureFromSurface(*renderer, assets.scenario)
	};
}
// Initialization functions moved from game.c




