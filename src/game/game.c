// game.c
#include "game.h"
#include "input/input.h"
#include "render/render.h"
#include "render/render_enemies.h"
#include "animation/animation.h"
#include "animation/animation_enemies.h"
#include "render/floor.h"

static void loadResources(SDL_Surface** scene, SDL_Surface** player, SDL_Surface** playerBack, SDL_Surface** soldier, FloorCoors* floor_coors);
static void initPlayerState(PlayerState* state);
static void initEnemiesState(EnemyState** ene_states, short enemy_count);
static void initScenarioState(ScenarioState* state);
static void updateAnimationTimers(PlayerState* state);
static void updateAnimationEnemyTimers(EnemyState* ene_states);

void startGame(SDL_Surface* screen, SDL_Window* window) {
    GRAPH g;
    ScenarioState sco_state;
    PlayerState player_state;
    EnemyState* ene_states;
    SDL_Surface *scenario = NULL, *player = NULL, *playerBack = NULL, *soldier = NULL;
    FloorCoors floor_coors;
    short enemy_count = 1;
    
    ene_states = malloc(sizeof(EnemyState) * 1);

    loadResources(&scenario, &player, &playerBack, &soldier, &floor_coors);

    player_state.quit = false;
    initPlayerState(&player_state);
    initEnemiesState(&ene_states, enemy_count);
    initScenarioState(&sco_state);

    g.screen = screen;
    g.window = window;
    g.player = player;
    g.playerBack = playerBack;
    g.soldier       = soldier;

    sco_state.screen = screen;
    sco_state.window = window;
    sco_state.scenario = scenario;
    sco_state.x = sco_state.xMountain = sco_state.xHorizon = 0;
    sco_state.floor_coors = &floor_coors;


    while (!player_state.quit) {
        handleEvents(&player_state);
        updateAnimationTimers(&player_state);
        renderScenario(&sco_state);
        renderPlayer(&player_state, &sco_state, &g); // aún por implementar
        renderUpdateCoors(&player_state, &sco_state);
        
        for(int i = 0; i < enemy_count; i++ ) {

            updateAnimationEnemyTimers(&ene_states[i]);
            renderEnemies(&ene_states[i], &g);
            renderUpdateEnemyCoors(&ene_states[i], &player_state, &sco_state);
            renderEnemyCollisions(&ene_states[i], &player_state, &sco_state);

        }

        SDL_UpdateWindowSurface(window);
    }

    free(floor_coors.coors);
    free(player_state.animation_arrays);
    free(ene_states);
    SDL_FreeSurface(scenario);
    SDL_FreeSurface(player);
    SDL_FreeSurface(playerBack);
}

static void loadResources(SDL_Surface** scene, SDL_Surface** player, SDL_Surface** playerBack, SDL_Surface** soldier, FloorCoors* floor_coors) {
    *scene =        IMG_Load("src/resources/backgrounds/fondo_mision_1.png");
    *player =       IMG_Load("src/resources/players/clark.png");
    *playerBack =   IMG_Load("src/resources/players/clarkBack.png");
    *soldier    =   IMG_Load("src/resources/enemies/soldier_enemy.png");
    floor_coors->coors = readFloorCoords("src/resources/coors/scene1-ground.txt", &floor_coors->count);

    if (!*scene) {
        printf("IMG_Load(Scene): %s\n", IMG_GetError());
        exit(-1);
    }
    if (!*player) {
        printf("IMG_Load(Player): %s\n", IMG_GetError());
        exit(-1);
    }
    if (!*playerBack) {
        printf("IMG_Load(PlayerBack): %s\n", IMG_GetError());
        exit(-1);
    }
    if (!*soldier) {
        printf("IMG_Load(Soldier): %s\n", IMG_GetError());
        exit(-1);
    }
}

static void initPlayerState(PlayerState* state) {
    AnimationArrays* ani_arrays;
    ani_arrays = malloc(sizeof(AnimationArrays));

    initAnimations(ani_arrays);

    *state = (PlayerState){
        .x = 0,
        .y = 0,
        .h = 25,
        .iTorso = 0,
        .iPierna = 0,
        .iShoot = 0,
        .X_RANGE_MIN = 20,
        .X_RANGE_MAX = 400,
        .sco_end_offset = 0,
        .x_displacement = 0,
        .iS = 0,
        .direction = DIRECTION_RIGHT,
        .directionAux = DIRECTION_RIGHT,
        .indexes = (Indexes) {4,1},
        .IS_RUNNING_BACKWARD = false,
        .IS_RUNNING_FORWARD = false,
        .key_up = false,
        .key_down = false,
        .run = false,
        .jump = false,
        .shoot = false,
        .key_shoot = false,
        .keepWalking = false,
        .jumpArr = false,
        .pastBreath = 0,
        .pastWalk = 0,
        .pastJump = 0,
        .pastShoot = 0,
        .quit = false,
        .animation_arrays = ani_arrays
    };
}

static void initEnemiesState(EnemyState** ene_states, short enemy_count) {
    AnimationEnemyArrays* ene_arrays;
    ene_arrays = malloc(sizeof(AnimationEnemyArrays));
    initEnemyAnimations(ene_arrays);

    for(int i = 0; i < enemy_count; i++ ) {
        *ene_states[i] = (EnemyState){
            .id = 1,
            .iBody = 0,
            .animate = false,
            .x = 450,
            .y = 0,
            .h = 450 + 25,
            .pastAnimate = 0,
            .y_offset = 24,
            .mode = MODE_CASUAL_1,
            .direction = DIRECTION_LEFT,
            .ani_arrays = ene_arrays
        };
    }
}

static void initScenarioState(ScenarioState* state) {
    *state = (ScenarioState){
        .x = 0,
        .y = 10,
        .x_mountain_offset_counter = 0,
        .x_horizon_offset_counter = 0,
        .X_MOUNTAIN_OFFSET = 4,
        .X_HORIZON_OFFSET = 18,
        .MAX_WIDTH = 3320
    };
}

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
    if(now > ene_states->pastAnimate + 110) {
        ene_states->animate = true;
        ene_states->pastAnimate = now;
    }
}
