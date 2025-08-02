// game.c
#include "game.h"
#include "input/input.h"
#include "render/render.h"
#include "render/render_enemies.h"
#include "animation/animation.h"
#include "animation/animation_enemies.h"
#include "render/floor.h"

#include <stdbool.h>

#define ENEMY_COUNT 5

typedef struct {
    SDL_Surface *scenario, *player, *player_back, *soldier;
    SDL_Texture *sco_texture, *pla_texture, *pla_texture_back;
} GameAssets;

static void loadResources(GameAssets* assets, FloorCoors* floor_coors);
static void initPlayer(PlayerState* state, GameAssets assets, SDL_Renderer** renderer);
static void initEnemies(EnemyState** ene_states, short count, GameAssets assets, SDL_Renderer** renderer);
static void initScenario(ScenarioState* state, GameAssets assets, SDL_Renderer** renderer);
static void gameLoop(GRAPH* g, GameAssets* assets, PlayerState* player, EnemyState** enemies, ScenarioState* scenario, short enemy_count);
static void updateAnimationTimers(PlayerState* state);
static void updateAnimationEnemyTimers(EnemyState* ene_states);
static void cleanupGame(GameAssets* assets, PlayerState* player, EnemyState** enemies, short enemy_count, FloorCoors* floor_coors);

void startGame(SDL_Renderer* renderer, SDL_Window* window) {
    GRAPH g = { .renderer = renderer, .window = window };
    GameAssets assets = {0};
    ScenarioState sco_state;
    PlayerState player_state;
    FloorCoors floor_coors;
    EnemyState** enemies = malloc(sizeof(EnemyState*) * ENEMY_COUNT);

    loadResources(&assets, &floor_coors);

    initPlayer(&player_state, assets, &renderer);
    initEnemies(enemies, ENEMY_COUNT, assets, &renderer);
    initScenario(&sco_state, assets, &renderer);

    sco_state.window = window;
    sco_state.floor_coors = &floor_coors;
    sco_state.x = sco_state.xMountain = sco_state.xHorizon = 0;

    gameLoop(&g, &assets, &player_state, enemies, &sco_state, ENEMY_COUNT);
    cleanupGame(&assets, &player_state, enemies, ENEMY_COUNT, &floor_coors);
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

static void loadResources(GameAssets* assets, FloorCoors* floor_coors) {
    assets->scenario = IMG_Load("src/resources/backgrounds/fondo_mision_1.png");
    assets->player = IMG_Load("src/resources/players/clark.png");
    assets->player_back = IMG_Load("src/resources/players/clarkBack.png");
    assets->soldier = IMG_Load("src/resources/enemies/soldier_enemy.png");

    floor_coors->coors = readFloorCoords("src/resources/coors/scene1-ground.txt", &floor_coors->count);

    if (!assets->scenario || !assets->player || !assets->player_back || !assets->soldier) {
        printf("Error cargando recursos: %s\n", IMG_GetError());
        exit(EXIT_FAILURE);
    }
}

static void initPlayer(PlayerState* state, GameAssets assets, SDL_Renderer** renderer) {
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

static void initEnemies(EnemyState** ene_states, short count, GameAssets assets, SDL_Renderer** renderer) {
    AnimationEnemyArrays* arrays = malloc(sizeof(AnimationEnemyArrays));
    initEnemyAnimations(arrays);

    SDL_Texture* _ene_texture = SDL_CreateTextureFromSurface(*renderer, assets.soldier);

    for (int i = 0; i < count; i++) {
        ene_states[i] = malloc(sizeof(EnemyState));
        *ene_states[i] = (EnemyState){
            .id = i, .x = 450 + i * 50, .h = 475 + i * 50, .y_offset = 24,
            .mode = MODE_CASUAL_1, .direction = DIRECTION_LEFT,
            .ani_arrays = arrays, .free_animation = true,
            .ene_texture = _ene_texture
        };
    }
}

static void initScenario(ScenarioState* state, GameAssets assets, SDL_Renderer** renderer) {
    *state = (ScenarioState){
        .x = 0,
        .y = 10,
        .w = 555,
        .X_MOUNTAIN_OFFSET = 4,
        .X_HORIZON_OFFSET = 18,
        .MAX_WIDTH = 3320,
        .sco_texture = SDL_CreateTextureFromSurface(*renderer, assets.scenario),
        .isScoTranslating = false
    };
}

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