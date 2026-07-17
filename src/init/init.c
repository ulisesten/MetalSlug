

#include "init.h"
#include "../game/game.h"
#include "../render/floor.h"
#include "../animation/animation_player_clark.h"
#include "../animation/animation_enemies.h"
#include "../animation/animation_bullets.h"
#include "../input/input.h"
#include "../utils/utils.h"
#include "../constants/scenario.h"
#include "../constants/player.h"
#include "../constants/enemies.h"
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

// ========================= Inicialización ==========================

void loadResources(GameAssets* assets, EnemyMatrix* matrix, FloorCoors* floor_coors) {
	assets->scenarioSurface = IMG_Load("src/resources/backgrounds/fondo_mision_1.png");
	assets->playerSurface = IMG_Load("src/resources/players/clark.png");
	assets->playerBackSurface = IMG_Load("src/resources/players/clarkBack.png");
	assets->soldierSurface = IMG_Load("src/resources/enemies/soldier_enemy.png");
	assets->bulletSurface = IMG_Load("src/resources/bullets/Weapon_SFX.png");

	matrix->matrix = readEnemyMatrix("src/resources/matrix/stage_1/enemies.txt", &matrix->count);
	floor_coors->coors = readFloorCoords("src/resources/coors/scene1-ground.txt", &floor_coors->count);

	if (!assets->scenarioSurface || !assets->playerSurface || !assets->playerBackSurface
	    || !assets->soldierSurface || !assets->bulletSurface) {
		printf("Error cargando recursos: %s\n", IMG_GetError());
		exit(EXIT_FAILURE);
	}
}

void initPlayer(PlayerState* state, GameAssets assets, SDL_Renderer** renderer) {
	AnimationArrays* ani_arrays = malloc(sizeof(AnimationArrays));
	initAnimations(ani_arrays);

	*state = (PlayerState){
		.x = 0,
		.y = 0,
		.floorIndex = PLAYER_START_FLOOR_INDEX,
		.fullscreen = false,
		.torsoFrame = 0,
		.legsFrame = 0,
		.shootFrame = 0,
		.jumpAnimFrame = 0,
		.jumpTrajectoryFrame = 0,
		.pendingShot = false,
		.lastBulletShotMs = 0,
		.X_RANGE_MIN = PLAYER_X_RANGE_MIN,
		.X_RANGE_MAX = PLAYER_X_RANGE_MAX,
		.direction = DIRECTION_RIGHT, .lastDirection = DIRECTION_RIGHT,
		.indexes = {.maxTorsoFrames = 4, .maxLegsFrames = 1},
		.animations = ani_arrays,
		.textureFront        = SDL_CreateTextureFromSurface(*renderer, assets.playerSurface),
		.textureBack   = SDL_CreateTextureFromSurface(*renderer, assets.playerBackSurface)
	};
}

void initEnemies(EnemyState** ene_states, EnemyMatrix* matrix, GameAssets assets, SDL_Renderer** renderer) {
	AnimationEnemyArrays* arrays = malloc(sizeof(AnimationEnemyArrays));
	initEnemyAnimations(arrays);

	SDL_Texture* shared_enemy_texture = SDL_CreateTextureFromSurface(*renderer, assets.soldierSurface);

	*ene_states = malloc(sizeof(EnemyState*) * (matrix->count));

	for (int i = 0; i < matrix->count; i++) {
		ene_states[i] = malloc(sizeof(EnemyState));
		*ene_states[i] = (EnemyState){
			.id = i,
			.x = matrix->matrix[i].x - ENEMY_SPAWN_X_OFFSET,
			.floorIndex = matrix->matrix[i].y,
			.spriteVerticalOffset = ENEMY_VERTICAL_OFFSET,
			.scenarioScrollOffset = 0,
			.type = matrix->matrix[i].type,
			.mode = matrix->matrix[i].mode,
			.direction = DIRECTION_LEFT,
			.animations = arrays,
			.canTransitionMode = true,
			.texture = shared_enemy_texture
		};
	}
}

void initScenario(ScenarioState* state, GameAssets assets, SDL_Renderer** renderer) {
	*state = (ScenarioState){
		.x = 0,
		.y = SCENARIO_BASE_Y,
		.w = SCENARIO_BASE_W,
		.MOUNTAIN_SCROLL_RATIO = MOUNTAIN_SCROLL_RATIO_VALUE,
		.HORIZON_SCROLL_RATIO = HORIZON_SCROLL_RATIO_VALUE,
		.SCENARIO_END_OFFSET = SCENARIO_END_OFFSET_VALUE,
		.maxScrollWidth = SCENARIO_MAX_WIDTH,
		.sco_texture = SDL_CreateTextureFromSurface(*renderer, assets.scenarioSurface),
		.jumpOffsetsCount = 52
	};
	clarkJump(state->jumpOffsets);
}

void initBullets(BulletPool* pool, GameAssets assets, SDL_Renderer** renderer) {
	SDL_Texture* tex = SDL_CreateTextureFromSurface(*renderer, assets.bulletSurface);
	AnimationBulletArrays* ani = malloc(sizeof(AnimationBulletArrays));
	initBulletAnimations(ani);
	initBulletPool(pool, tex);
	pool->anim = ani;
}
// Initialization functions moved from game.c
