// game.c
#include "game.h"
#include "input/input.h"
#include "render/render.h"
#include "render/render_enemies.h"
#include "animation/animation_player_clark.h"
#include "animation/animation_enemies.h"
#include "animation/animation_bullets.h"
#include "render/floor.h"

#include "init/init.h"
#include "constants/timers.h"
#include "constants/bullets.h"
#include "constants/player.h"

#include <stdbool.h>

#define MAX_ENEMIES 5


// Declarations moved to init.h
static void gameLoop(       GRAPH* g, GameAssets* assets, PlayerState* player, EnemyState** enemies, ScenarioState* scenario, BulletPool* bullets, short enemy_count);
static void updateAnimationTimers(      PlayerState* state);
static void updateAnimationEnemyTimers( EnemyState* ene_states);
static void updateBullets(BulletPool* pool);
static void spawnBulletFromPlayer(PlayerState* player, BulletPool* pool);
static void cleanupGame(    GameAssets* assets, PlayerState* player, EnemyState** enemies, BulletPool* bullets, short enemy_count, FloorCoors* floor_coors);

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
    BulletPool bullets;

    loadResources(&assets, &matrix, &floor_coors);

    EnemyState** enemies = malloc(sizeof(EnemyState*) * matrix.count);
    if (!enemies) {
        fprintf(stderr, "Memory allocation failed for enemies\n");
        cleanupGame(&assets, &player_state, NULL, &bullets, 0, &floor_coors);
        return;
    }

    initPlayer(&player_state, assets, &renderer);
    initEnemies(enemies, &matrix, assets, &renderer);
    initScenario(&sco_state, assets, &renderer);
    initBullets(&bullets, assets, &renderer);

    sco_state.window = window;
    sco_state.floor_coors = &floor_coors;
    sco_state.x = sco_state.mountainScrollX = sco_state.horizonScrollX = 0;

    gameLoop(&g, &assets, &player_state, enemies, &sco_state, &bullets, matrix.count);
    cleanupGame(&assets, &player_state, enemies, &bullets, matrix.count, &floor_coors);
}

/**
 * @brief Main game loop that handles rendering, updates, and input
 */
static void gameLoop(GRAPH* g, GameAssets* assets, PlayerState* player, EnemyState** enemies, ScenarioState* scenario, BulletPool* bullets, short enemy_count) {
    (void)assets;
    while (!player->quit) {
        SDL_RenderClear(g->renderer);

        handleEvents(player);
        updateAnimationTimers(player);

        /* One bullet per physical key press, throttled by BULLET_COOLDOWN_MS.
         * The pendingShot edge flag is set in input.c only when repeat == 0
         * (no auto-repeat), so a held key never produces a stream of bullets. */
        Uint32 now = SDL_GetTicks();
        if (player->pendingShot &&
            (now - player->lastBulletShotMs) >= BULLET_COOLDOWN_MS) {
            player->pendingShot     = false;
            player->lastBulletShotMs = now;
            spawnBulletFromPlayer(player, bullets);
        }

        renderScenario(g, scenario);
        renderPlayer(player, scenario, g);
        renderUpdateCoors(player, scenario);
        updateBullets(bullets);
        renderBullets(g, bullets);

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

    if (now > state->lastJumpAnimTick + JUMP_ANIM_INTERVAL_MS) {
        state->shouldAdvanceJumpAnim = true;
        state->lastJumpAnimTick = now;
    }

    if (now > state->lastJumpTrajectoryTick + JUMP_TRAJECTORY_INTERVAL_MS) {
        state->shouldAdvanceJumpTrajectory = true;
        state->lastJumpTrajectoryTick = now;
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

// ========================= Bullets ==========================

static void spawnBulletFromPlayer(PlayerState* player, BulletPool* pool) {
    /* player->y already includes the jump offset at this point because
     * renderPlayer ran in the previous frame; at the very first frame of the
     * game (before any render) it still holds the initial value from
     * initPlayer, which is fine for spawning. The bullet snapshots this y
     * and never tracks the player again. */
    int spawn_x = player->x + BULLET_SPAWN_OFFSET_X;
    /* Facing left → sprite is mirrored, muzzle sits 8px further left than
     * the default forward offset. */
    if (player->direction == DIRECTION_LEFT) {
        spawn_x -= BULLET_SPAWN_OFFSET_X_LEFT_CORRECTION;
    }
    int spawn_y = player->y + BULLET_SPAWN_OFFSET_Y;
    spawnBullet(pool, spawn_x, spawn_y, player->direction);
}

static void updateBullets(BulletPool* pool) {
    Uint32 now = SDL_GetTicks();
    for (int i = 0; i < BULLET_POOL_CAPACITY; i++) {
        BulletState* b = &pool->bullets[i];
        if (!b->active) continue;

        /* Timer-driven horizontal advance: each BULLET_ADVANCE_INTERVAL_MS
         * the bullet moves BULLET_ADVANCE_STEP_X pixels (FPS-independent). */
        if ((int)(now - b->lastAdvanceMs) >= BULLET_ADVANCE_INTERVAL_MS) {
            b->x += b->dx * BULLET_ADVANCE_STEP_X;
            b->lastAdvanceMs = now;
        }

        /* y is NOT touched: it stays at spawn value forever, so a player
         * returning to the ground doesn't drag the bullet down with them. */

        /* Despawn after travelling BULLET_TRAVEL_RANGE pixels or going
         * well outside the visible viewport. */
        int dx_from_start = b->x - b->start_x;
        if (dx_from_start >  BULLET_TRAVEL_RANGE ||
            dx_from_start < -BULLET_TRAVEL_RANGE ||
            b->x < -100 || b->x > 5000) {
            b->active = false;
        }
    }
}

// ========================= Limpieza ==========================

static void cleanupGame(GameAssets* assets, PlayerState* player, EnemyState** enemies, BulletPool* bullets, short enemy_count, FloorCoors* floor_coors) {
    for (int i = 0; i < enemy_count; i++)
        free(enemies[i]);
    free(enemies);
    free(player->animations);
    free(floor_coors->coors);

    if (bullets) {
        if (bullets->texture) SDL_DestroyTexture(bullets->texture);
        free(bullets->anim);
    }

    SDL_FreeSurface(assets->scenarioSurface);
    SDL_FreeSurface(assets->playerSurface);
    SDL_FreeSurface(assets->playerBackSurface);
    SDL_FreeSurface(assets->soldierSurface);
}
