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
static void gameLoop(       GRAPH* g, GameAssets* assets, PlayerState* player, EnemyState** enemies, ScenarioState* scenario, BulletPool* bullets, short* enemy_count);
static void updateAnimationTimers(      PlayerState* state);
static void updateAnimationEnemyTimers( EnemyState* ene_states);
static void updateBullets(BulletPool* pool, EnemyState** enemies, short enemy_count);
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

    short enemy_count = matrix.count;
    gameLoop(&g, &assets, &player_state, enemies, &sco_state, &bullets, &enemy_count);
    cleanupGame(&assets, &player_state, enemies, &bullets, enemy_count, &floor_coors);
}

/**
 * @brief Main game loop that handles rendering, updates, and input
 */
static void gameLoop(GRAPH* g, GameAssets* assets, PlayerState* player, EnemyState** enemies, ScenarioState* scenario, BulletPool* bullets, short* enemy_count) {
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
        updateBullets(bullets, enemies, *enemy_count);
        renderBullets(g, bullets);

        for (int i = 0; i < *enemy_count; i++) {
            updateAnimationEnemyTimers(enemies[i]);
            renderEnemies(enemies[i], g);
            renderUpdateEnemyCoors(enemies[i], player, scenario);
            renderEnemyCollisions(enemies[i], player, scenario);
        }

        /* Compact enemy array: remove the ones who finished blinking.
         * We free their memory, shift the rest down, and decrease count. */
        for (int i = 0; i < *enemy_count; ) {
            if (enemies[i]->shouldRemove) {
                free(enemies[i]);
                for (int k = i; k < *enemy_count - 1; k++) {
                    enemies[k] = enemies[k + 1];
                }
                enemies[*enemy_count - 1] = NULL;
                (*enemy_count)--;
            } else {
                i++;
            }
        }

        /* Debug overlay (F1) — drawn last so it sits above every sprite. */
        renderDebugRects(g, player, enemies, *enemy_count);

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

    /* Death animation timer. While shouldDie is true, advances deadFrame
     * every DEATH_ANIM_INTERVAL_MS; caps at the last frame and sets isDead
     * so the player lingers. Once isDead is true the flag flips off and the
     * timer is no longer consulted. */
    if (state->shouldDie && !state->isDead
        && (now > state->lastDeadTick + DEATH_ANIM_INTERVAL_MS)) {
        state->shouldAdvanceDeathAnim = true;
        state->lastDeadTick = now;
    }

    if (now > state->lastTranslateTick + TRANSLATE_INTERVAL_MS) {
        state->shouldTranslate = true;
        state->lastTranslateTick = now;
    }
}

static void updateAnimationEnemyTimers(EnemyState* ene_states){
    Uint32 now = SDL_GetTicks();

    if(now > ene_states->lastAnimateTick + ENEMY_ANIMATE_INTERVAL_MS) {
        ene_states->shouldAnimate = true;
        ene_states->lastAnimateTick = now;
    }

    if(now > ene_states->lastWalkTick + ENEMY_WALK_INTERVAL_MS) {
        ene_states->shouldWalk = true;
        ene_states->lastWalkTick = now;
    }

    /* Death-by-bullet animation: advance deadFrame on each interval. */
    if (ene_states->isDying
        && (now > ene_states->lastDeadTick + ENEMY_DEAD_ANIM_INTERVAL_MS)) {
        ene_states->deadFrame++;
        ene_states->lastDeadTick = now;
        if (ene_states->deadFrame >= ENEMY_DEAD_FRAMES) {
            /* Death animation done → switch to blinking phase.
             * Park the enemy off-screen so the visible sprite disappears
             * immediately while the blink timer counts down (the blink
             * is purely a cooldown before the slot is reclaimed). */
            ene_states->x = -10000;
            ene_states->isDying = false;
            ene_states->isBlinking = true;
            ene_states->deadFrame = ENEMY_DEAD_FRAMES - 1;
            ene_states->blinkFrame = 0;
            ene_states->lastBlinkTick = now;
        }
    }

    /* Blinking: advance blink counter every interval, then mark for removal. */
    if (ene_states->isBlinking
        && (now > ene_states->lastBlinkTick + ENEMY_BLINK_INTERVAL_MS)) {
        ene_states->blinkFrame++;
        ene_states->lastBlinkTick = now;
        if (ene_states->blinkFrame >= ENEMY_BLINK_FRAMES * 2) {
            ene_states->isBlinking = false;
            ene_states->shouldRemove = true;
        }
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

static void updateBullets(BulletPool* pool, EnemyState** enemies, short enemy_count) {
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

        /* Bullet AABB for collision (b->x,y is top-left). */
        SDL_Rect bullet_rect = { b->x, b->y, BULLET_WIDTH, BULLET_HEIGHT };

        /* Check against every live enemy. Hit → mark enemy isDying, despawn
         * the bullet. First hit only; bullet disappears on touching. */
        bool hit = false;
        for (int j = 0; j < enemy_count; j++) {
            EnemyState* e = enemies[j];
            if (!e || e->isDead || e->isDying || e->isBlinking || e->shouldRemove) continue;
            if (e->lastBodyDstRect.w <= 0 || e->lastBodyDstRect.h <= 0) continue;

            if (SDL_HasIntersection(&bullet_rect, &e->lastBodyDstRect)) {
                e->isDying = true;
                e->deadFrame = 0;
                e->lastDeadTick = now;
                hit = true;
                break;
            }
        }
        if (hit) {
            b->active = false;
            continue;
        }

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
