// render.c
#include "render.h"
#include <SDL2/SDL.h>
#include "../animation/animation_player_clark.h"
#include "../animation/animation_bullets.h"
#include "../animation/animation_enemies.h"
#include "floor.h"
#include "constants/scenario.h"

static void ToggleFullscreen(SDL_Window* window) {

    /* Use FULLSCREEN_DESKTOP so the display keeps its current desktop
     * resolution and SDL scales our logical WINDOW_WIDTH×WINDOW_HEIGHT
     * render target up to fill the screen. Plain SDL_WINDOW_FULLSCREEN
     * would switch the display to a (possibly different) video mode and
     * leave large black borders around our fixed-size render. */
    Uint32 FullscreenFlag = SDL_WINDOW_FULLSCREEN_DESKTOP;

    bool IsFullscreen = SDL_GetWindowFlags(window) & FullscreenFlag;
    SDL_SetWindowFullscreen(window, IsFullscreen ? 0 : FullscreenFlag);
    SDL_ShowCursor(IsFullscreen);

}

void renderScenario(GRAPH* g, ScenarioState* sco_state) {
    SDL_Rect cielo = { SKY_SRC_X + sco_state->horizonScrollX, 408, SKY_SRC_W, SKY_SRC_H };
    SDL_Rect horizon_coors = { 0, 0, HORIZON_DEST_W, HORIZON_DEST_H };
    SDL_Rect mountains = { MOUNTAIN_DEST_X + sco_state->mountainScrollX, MOUNTAIN_DEST_Y, MOUNTAIN_SRC_W, MOUNTAIN_SRC_H };
    SDL_Rect mountain_coors = { 0, MOUNTAIN_COORS_Y, MOUNTAIN_SRC_W, MOUNTAIN_COORS_H };
    SDL_Rect tierra = { GROUND_SRC_X + sco_state->x, sco_state->y, GROUND_DEST_W, GROUND_DEST_H };
    //SDL_Rect tierra = { 10, sco_state->y, 502, 250 };
    SDL_Rect tierra_coors = { GROUND_COORS_X, GROUND_COORS_Y, GROUND_COORS_W, GROUND_COORS_H };

    SDL_RenderCopy(g->renderer, sco_state->sco_texture, &cielo, &horizon_coors);
    SDL_RenderCopy(g->renderer, sco_state->sco_texture, &mountains, &mountain_coors);
    SDL_RenderCopy(g->renderer, sco_state->sco_texture, &tierra, &tierra_coors);
}

void renderPlayer(PlayerState* pla_state, ScenarioState* sco_state, GRAPH* g) {
    /* Lock vertical position to terrain unless jumping. While jumping,
     * pla_state->y carries the effective on-screen Y (ground - jumpOffset)
     * so anything that tracks the player (e.g. bullets) follows it. */
    int ground_y = pla_state->y;
    if(pla_state->floorIndex >= 0 && pla_state->floorIndex < sco_state->floor_coors->count) {
        ground_y = sco_state->floor_coors->coors[pla_state->floorIndex];
    }

    if(pla_state->shouldJump && sco_state->jumpOffsetsCount > 0) {
        int idx = pla_state->jumpTrajectoryFrame;
        if (idx < 0) idx = 0;
        if (idx >= sco_state->jumpOffsetsCount) idx = sco_state->jumpOffsetsCount - 1;
        pla_state->y = ground_y - sco_state->jumpOffsets[idx];
    } else {
        pla_state->y = ground_y;
    }

    if(pla_state->fullscreen) {
        ToggleFullscreen(g->window);
        pla_state->fullscreen = false;  /* consume the edge */
    }

    pla_state->indexes = animate_clark(g, sco_state, pla_state, pla_state->animations);
}

void renderUpdateCoors(PlayerState* pla_state, ScenarioState* sco_state) {

    //printf("x: %d, h: %d, sco: %d\n", pla_state->x, pla_state->floorIndex, sco_state->x);
    const int mountainRatio = sco_state->MOUNTAIN_SCROLL_RATIO;
    const int horizonRatio  = sco_state->HORIZON_SCROLL_RATIO;

    /* Dead player can't move (inputs were also ignored in handleEvents).
     * We still draw the corpse anchored to the terrain below. */
    const bool dead = pla_state->shouldDie || pla_state->isDead;

    if( !dead && pla_state->isMovingForward ) {
        if( sco_state->x >= sco_state->maxScrollWidth -1 ) pla_state->endOfScenarioOffset = sco_state->SCENARIO_END_OFFSET;

        if(pla_state->shouldTranslate) {
            if( pla_state->x < pla_state->X_RANGE_MAX + pla_state->endOfScenarioOffset ){
                pla_state->x++;
            }else{
                if( sco_state->x < sco_state->maxScrollWidth ) {
                    sco_state->x++;
                    sco_state->w++;
                    sco_state->mountainOffsetCounter++;
                }

                if(sco_state->mountainOffsetCounter >= mountainRatio) {
                    sco_state->mountainScrollX++;
                }
            }

            if(pla_state->floorIndex <= sco_state->floor_coors->count){
                pla_state->floorIndex++;
            }
        }     
    }
    
    else
    if( !dead && pla_state->isMovingBackward ) {
        if(pla_state->shouldTranslate) {
            if(pla_state->floorIndex > 0 && pla_state->x > 0){
                pla_state->x--;
                pla_state->floorIndex--;
            }
        }  
        
    } else {
        if(!pla_state->shouldJump && !pla_state->wantToShoot){
            pla_state->isRunning = false;
        }
    }

    if(sco_state->mountainOffsetCounter >= mountainRatio)
        sco_state->mountainOffsetCounter = 0;

    pla_state->shouldBreathe               = false;
    pla_state->shouldRun                  = false;
    pla_state->shouldTranslate            = false;
    pla_state->shouldShoot                = false;
    pla_state->shouldAdvanceJumpAnim      = false;
    pla_state->shouldAdvanceJumpTrajectory = false;
}

void renderBullets(GRAPH* g, BulletPool* pool) {
    if (!pool || !pool->texture || !pool->anim) return;
    for (int i = 0; i < BULLET_POOL_CAPACITY; i++) {
        BulletState* b = &pool->bullets[i];
        if (!b->active) continue;

        SDL_Rect src;
        getBulletSrcRect(b->type, pool->anim, b->frame, &src);
        if (src.w == 0 || src.h == 0) continue; /* sprite not configured yet */

        int draw_x = b->x;
        int draw_y = b->y;
        if (b->dx < 0) {
            /* Sprite faces right by default; flip horizontally when firing left */
            SDL_Rect dst = { draw_x - src.w, draw_y, src.w, src.h };
            SDL_RenderCopyEx(g->renderer, pool->texture, &src, &dst, 0.0, NULL, SDL_FLIP_HORIZONTAL);
        } else {
            SDL_Rect dst = { draw_x, draw_y, src.w, src.h };
            SDL_RenderCopy(g->renderer, pool->texture, &src, &dst);
        }
    }
}

/* === Debug === Toggled by F1. Draws coloured outlines around the player
 * sprite parts (torso red, legs cyan when on-screen) and each live enemy
 * body (yellow), using the cached destination rects written by
 * animate_clark and the soldier* functions. */
void renderDebugRects(GRAPH* g, PlayerState* pla, EnemyState** enemies, int enemy_count) {
    if (!pla->showDebugRects) return;

    /* First-run confirmation — helps spot if rects are never populated. */
    static int shown = 0;
    if (shown++ == 0) {
        printf("[DEBUG] Drawing AABBs. Player torso {%d,%d,%d,%d} legs {%d,%d,%d,%d}\n",
               pla->lastTorsoDstRect.x, pla->lastTorsoDstRect.y,
               pla->lastTorsoDstRect.w, pla->lastTorsoDstRect.h,
               pla->lastLegsDstRect.x,  pla->lastLegsDstRect.y,
               pla->lastLegsDstRect.w,  pla->lastLegsDstRect.h);
    }

    /* Player torso — red. */
    if (pla->lastTorsoDstRect.w > 0 && pla->lastTorsoDstRect.h > 0) {
        SDL_SetRenderDrawColor(g->renderer, 255, 0, 0, 255);
        SDL_RenderDrawRect(g->renderer, &pla->lastTorsoDstRect);
    }
    /* Player legs — cyan, but only when on-screen (the death animator parks
     * them at (-10000,-10000) — drawing a rect there is harmless but
     * visually noisy). */
    if (pla->lastLegsDstRect.w > 0 && pla->lastLegsDstRect.h > 0
        && pla->lastLegsDstRect.x > -100) {
        SDL_SetRenderDrawColor(g->renderer, 0, 255, 255, 255);
        SDL_RenderDrawRect(g->renderer, &pla->lastLegsDstRect);
    }

    /* Enemies — yellow. */
    SDL_SetRenderDrawColor(g->renderer, 255, 255, 0, 255);
    for (int i = 0; i < enemy_count; i++) {
        EnemyState* e = enemies[i];
        if (e->isDead) continue;
        if (e->lastBodyDstRect.w > 0 && e->lastBodyDstRect.h > 0) {
            SDL_RenderDrawRect(g->renderer, &e->lastBodyDstRect);
        }
    }
}
