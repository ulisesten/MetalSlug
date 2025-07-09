// game.c
#include "game.h"
#include "input/input.h"
#include "render/render.h"
#include "render/animation.h"
#include "render/floor.h"

static void loadResources(SDL_Surface** scene, SDL_Surface** player, SDL_Surface** playerBack, FloorCoors* floor_coors);
static void initPlayerState(PlayerState* state);
static void initScenarioState(ScenarioState* state);
static void updateAnimationTimers(PlayerState* state);

void startGame(SDL_Surface* screen, SDL_Window* window) {
    GRAPH g;
    ScenarioState sco_state;
    PlayerState player_state;
    SDL_Surface *scenario = NULL, *player = NULL, *playerBack = NULL;
    FloorCoors floor_coors;

    loadResources(&scenario, &player, &playerBack, &floor_coors);

    player_state.quit = false;
    initPlayerState(&player_state);
    initScenarioState(&sco_state);

    g.screen = screen;
    g.window = window;
    g.player = player;
    g.playerBack = playerBack;
    player_state.floor_coors = &floor_coors;

    sco_state.screen = screen;
    sco_state.window = window;
    sco_state.scenario = scenario;
    sco_state.x = sco_state.xMountain = sco_state.xHorizon = 0;

    AnimationArrays ani_arrays;
    initAnimations(&ani_arrays);

    player_state.animation_arrays = &ani_arrays;

    while (!player_state.quit) {
        handleEvents(&player_state);
        updateAnimationTimers(&player_state);
        renderScenario(&sco_state);
        renderPlayer(&player_state, &g); // aún por implementar
        renderUpdateCoors(&player_state, &sco_state);
        SDL_UpdateWindowSurface(window);
    }

    free(floor_coors.coors);
    SDL_FreeSurface(scenario);
    SDL_FreeSurface(player);
    SDL_FreeSurface(playerBack);
}

static void loadResources(SDL_Surface** scene, SDL_Surface** player, SDL_Surface** playerBack, FloorCoors* floor_coors) {
    *scene =        IMG_Load("src/resources/backgrounds/fondo_mision_1.png");
    *player =       IMG_Load("src/resources/players/clark.png");
    *playerBack =   IMG_Load("src/resources/players/clarkBack.png");
    floor_coors->coors = readFloorCoords("src/resources/coors/scene1-ground.txt", &floor_coors->count);
}

static void initPlayerState(PlayerState* state) {
    *state = (PlayerState){
        .x = -25,
        .y = 0,
        .h = 0,
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
        .key_left = false,
        .key_right = false,
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
        .quit = false
    };
}

static void initScenarioState(ScenarioState* state) {
    *state = (ScenarioState){
        .x = 0,
        .y = 10,
        .x_mountain_offset = 0,
        .x_horizon_offset = 0,
        .MAX_WIDTH = 3320
    };
}

static void updateAnimationTimers(PlayerState* state) {
    Uint32 now = SDL_GetTicks();

    if (now > state->pastBreath + 200) {
        state->breath = true;
        state->pastBreath = now;
    }

    if (now > state->pastWalk + 100) {
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

    if (now > state->pastTime + 10) {
        state->translate = true;
        state->pastTime = now;
    }
}
