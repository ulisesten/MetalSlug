// game.c
#include "game.h"
#include "input/input.h"
#include "render/render.h"
#include "render/render_enemies.h"
#include "animation/animation.h"
#include "animation/animation_enemies.h"
#include "render/floor.h"

#include "init/init.h"
#include "constants/timers.h"

#include <stdbool.h>

#define MAX_ENEMIES 5


// Declarations moved to init.h
static void gameLoop(       GRAPH* g, GameAssets* assets, PlayerState* player, EnemyState** enemies, ScenarioState* scenario, short enemy_count);
static void updateAnimationTimers(      PlayerState* state);
static void updateAnimationEnemyTimers( EnemyState* ene_states);
static void cleanupGame(    GameAssets* assets, PlayerState* player, EnemyState** enemies, short enemy_count, FloorCoors* floor_coors);

void startGame(SDL_Renderer* renderer, SDL_Window* window) {
    if (!renderer || !window) {
        fprintf(stderr, "Invalid renderer or window\n");
        return;
    }

    GRAPH g = { .renderer = renderer, .window = window };
    GameAssets assets = {0};
    ScenarioState sco_state;
    PlayerState player_state;
    FloorCoors floor_coors;
    EnemyMatrix matrix;
    
    loadResources(&assets, &matrix, &floor_coors);

    EnemyState** enemies = malloc(sizeof(EnemyState*) * matrix.count);
    if (!enemies) {
        fprintf(stderr, "Memory allocation failed for enemies\n");
        cleanupGame(&assets, &player_state, NULL, 0, &floor_coors);
        return;
    }

    initPlayer(&player_state, assets, &renderer);
    initEnemies(enemies, &matrix, assets, &renderer);
    initScenario(&sco_state, assets, &renderer);

    sco_state.window = window;
    sco_state.floor_coors = &floor_coors;
    sco_state.x = sco_state.mountainScrollX = sco_state.horizonScrollX = 0;

    gameLoop(&g, &assets, &player_state, enemies, &sco_state, matrix.count);
    cleanupGame(&assets, &player_state, enemies, matrix.count, &floor_coors);
}

/**
 * @brief Main game loop that handles rendering, updates, and input
 *
 * @param g Graphics context containing renderer and window
 * @param assets Game assets (textures, surfaces, etc.)
 * @param player Player state and animation data
 * @param enemies Array of enemy states
 * @param scenario Scenario/level state
 * @param enemy_count Number of enemies in the array
 */
static void gameLoop(GRAPH* g, GameAssets* assets, PlayerState* player, EnemyState** enemies, ScenarioState* scenario, short enemy_count) {
    while (!player->quit) {
        SDL_RenderClear(g->renderer);

        handleEvents(player);
        updateAnimationTimers(player);
        renderScenario(g, scenario);
        renderPlayer(player, scenario, g);
        renderUpdateCoors(player, scenario);

        for (int i = 0; i < enemy_count; i++) {
            updateAnimationEnemyTimers(enemies[i]);
            renderEnemies(enemies[i], g);
            renderUpdateEnemyCoors(enemies[i], player, scenario);
            renderEnemyCollisions(enemies[i], player, scenario);
        }

        SDL_RenderPresent(g->renderer);
    }
}

// ========================= Inicialización ==========================
// Implementations moved to init/init.c

// ========================= Timers ==========================

static void updateAnimationTimers(PlayerState* state) {
    Uint32 now = SDL_GetTicks();

    if (now > state->lastBreathTick + BREATH_INTERVAL_MS) {
        state->shouldBreathe = true;
        state->lastBreathTick = now;
    }

    if (now > state->lastWalkTick + WALK_INTERVAL_MS) {
        state->shouldRun = true;
        state->lastWalkTick = now;
    }

    if (now > state->lastJumpTick + JUMP_INTERVAL_MS) {
        state->shouldUpdateJump = true;
        state->lastJumpTick = now;
    }

    if (now > state->lastShootTick + SHOOT_INTERVAL_MS) {
        state->shouldShoot = true;
        state->lastShootTick = now;
    }

    if (now > state->lastTranslateTick + TRANSLATE_INTERVAL_MS) {
        state->shouldTranslate = true;
        state->lastTranslateTick = now;
    }
}

static void updateAnimationEnemyTimers(EnemyState* ene_states){
    Uint32 now = SDL_GetTicks();
    
    // 110
    if(now > ene_states->lastAnimateTick + ENEMY_ANIMATE_INTERVAL_MS) {
        ene_states->shouldAnimate = true;
        ene_states->lastAnimateTick = now;
    }

    if(now > ene_states->lastWalkTick + ENEMY_WALK_INTERVAL_MS) {
        ene_states->shouldWalk = true;
        ene_states->lastWalkTick = now;
    }
}

// ========================= Limpieza ==========================

static void cleanupGame(GameAssets* assets, PlayerState* player, EnemyState** enemies, short enemy_count, FloorCoors* floor_coors) {
    for (int i = 0; i < enemy_count; i++)
        free(enemies[i]);
    free(enemies);
    free(player->animations);
    free(floor_coors->coors);

    SDL_FreeSurface(assets->scenarioSurface);
    SDL_FreeSurface(assets->playerSurface);
    SDL_FreeSurface(assets->playerBackSurface);
    SDL_FreeSurface(assets->soldierSurface);
}
