// render.c
#include "render.h"
#include <SDL2/SDL.h>
#include "../animation/animation.h"
#include "floor.h"
#include "constants/scenario.h"

static void ToggleFullscreen(SDL_Window* window) {

    Uint32 FullscreenFlag = SDL_WINDOW_FULLSCREEN;

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
    static SDL_Rect torso[10];
    static SDL_Rect pierna[6];

    if(pla_state->floorIndex >= 0 && pla_state->floorIndex < sco_state->floor_coors->count)
        pla_state->y = sco_state->floor_coors->coors[pla_state->floorIndex];

    if(pla_state->fullscreen) {
        ToggleFullscreen(g->window);
    }

    switch (pla_state->direction) {
        case DIRECTION_RIGHT:
            if (pla_state->isMovingForward) {
                pla_state->indexes = clarkRunV2(g, pla_state, pla_state->animations);
            } 
            else 
            if (pla_state->shotsRemaining) {
                clarkShootArr(torso);
                pla_state->indexes =
                    clarkShoot(*g, &pla_state->torsoFrame, pla_state->x, pla_state->y, torso);
            } else {
                pla_state->indexes = clarkStandV2(g, pla_state, *pla_state->animations);
            }
            break;

        case DIRECTION_LEFT:
            if (pla_state->isMovingBackward) {
                pla_state->indexes = clarkRunBackV2(g, pla_state, pla_state->animations);
            } else {
                pla_state->indexes = clarkStandBackV2(g, pla_state, pla_state->animations);
            }
            break;
    }

    
}

void renderUpdateCoors(PlayerState* pla_state, ScenarioState* sco_state) {

    //printf("x: %d, h: %d, sco: %d\n", pla_state->x, pla_state->floorIndex, sco_state->x);
    const int mountainRatio = sco_state->MOUNTAIN_SCROLL_RATIO;
    const int horizonRatio  = sco_state->HORIZON_SCROLL_RATIO;

    if( pla_state->isMovingForward ) {
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
    if( pla_state->isMovingBackward ) {
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


    if(pla_state->shouldBreathe) pla_state->torsoFrame++;
    if(pla_state->shouldRun) pla_state->legsFrame++;

    if( pla_state->legsFrame >= pla_state->indexes.maxLegsFrames ) pla_state->legsFrame = 0;
    if( pla_state->torsoFrame  >= pla_state->indexes.maxTorsoFrames  ) pla_state->torsoFrame  = 0;

    if(sco_state->mountainOffsetCounter >= mountainRatio)
        sco_state->mountainOffsetCounter = 0;

    pla_state->shouldBreathe       = false;
    pla_state->shouldRun          = false;
    pla_state->shouldTranslate    = false;
    pla_state->shouldShoot        = false;
}
