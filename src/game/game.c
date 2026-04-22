// game.c
#include "game.h"
#include "input/input.h"
#include "render/render.h"
#include "render/render_enemies.h"
#include "animation/animation.h"
#include "animation/animation_enemies.h"
#include "render/floor.h"

#include "init/init.h"

#include <stdbool.h>

#define ENEMY_COUNT 5


// Declarations moved to init.h
static void gameLoop(       GRAPH* g, GameAssets* assets, PlayerState* player, EnemyState** enemies, ScenarioState* scenario, short enemy_count);
static void updateAnimationTimers(      PlayerState* state);
static void updateAnimationEnemyTimers( EnemyState* ene_states);
static void cleanupGame(    GameAssets* assets, PlayerState* player, EnemyState** enemies, short enemy_count, FloorCoors* floor_coors);

void startGame(SDL_Renderer* renderer, SDL_Window* window) {
    GRAPH g = { .renderer = renderer, .window = window };
    GameAssets assets = {0};
    ScenarioState sco_state;
    PlayerState player_state;
    FloorCoors floor_coors;
    EnemyMatrix matrix;
    
    loadResources(&assets, &matrix, &floor_coors);

    EnemyState** enemies = malloc(sizeof(EnemyState*) * matrix.count);

    initPlayer(&player_state, assets, &renderer);
    initEnemies(enemies, &matrix, assets, &renderer);
    initScenario(&sco_state, assets, &renderer);

    sco_state.window = window;
    sco_state.floor_coors = &floor_coors;
    sco_state.x = sco_state.xMountain = sco_state.xHorizon = 0;

    gameLoop(&g, &assets, &player_state, enemies, &sco_state, matrix.count);
    cleanupGame(&assets, &player_state, enemies, matrix.count, &floor_coors);
}

// ========================= Loop principal ==========================

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

    if (now > state->pastBreath + 200) {
        state->breath = true;
        state->pastBreath = now;
    }

    if (now > state->pastWalk + 94) {
        state->run = true;
        state->pastWalk = now;
    }

    if (now > state->pastJump + 10) {
        state->jumpArr = true;
        state->pastJump = now;
    }

    if (now > state->pastShoot + 20) {
        state->shoot = true;
        state->pastShoot = now;
    }

    if (now > state->pastTime + 9) {
        state->translate = true;
        state->pastTime = now;
    }
}

static void updateAnimationEnemyTimers(EnemyState* ene_states){
    Uint32 now = SDL_GetTicks();
    
    // 110
    if(now > ene_states->pastAnimate + 90) {
        ene_states->animate = true;
        ene_states->pastAnimate = now;
    }

    if(now > ene_states->pastWalk + 20) {
        ene_states->walk = true;
        ene_states->pastWalk = now;
    }
}

// ========================= Limpieza ==========================

static void cleanupGame(GameAssets* assets, PlayerState* player, EnemyState** enemies, short enemy_count, FloorCoors* floor_coors) {
    for (int i = 0; i < enemy_count; i++)
        free(enemies[i]);
    free(enemies);
    free(player->animation_arrays);
    free(floor_coors->coors);

    SDL_FreeSurface(assets->scenario);
    SDL_FreeSurface(assets->player);
    SDL_FreeSurface(assets->player_back);
    SDL_FreeSurface(assets->soldier);
}