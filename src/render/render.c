// render.c
#include "render.h"
#include <SDL2/SDL.h>
#include "../animation/animation.h"
#include "floor.h"

static void ToggleFullscreen(SDL_Window* window) {

    Uint32 FullscreenFlag = SDL_WINDOW_FULLSCREEN;

    bool IsFullscreen = SDL_GetWindowFlags(window) & FullscreenFlag;
    SDL_SetWindowFullscreen(window, IsFullscreen ? 0 : FullscreenFlag);
    SDL_ShowCursor(IsFullscreen);

}

void renderScenario(GRAPH* g, ScenarioState* sco_state) {
    SDL_Rect cielo = { 10 + sco_state->xHorizon, 408, 560, 112 };
    SDL_Rect horizon_coors = { 0, 0, 555, 180 };
    SDL_Rect mountains = { 10 + sco_state->xMountain, 560, 502, 168 };
    SDL_Rect mountain_coors = { 0, 57, 502, 180 };
    SDL_Rect tierra = { 10 + sco_state->x, sco_state->y, 502, 250 };
    //SDL_Rect tierra = { 10, sco_state->y, 502, 250 };
    SDL_Rect tierra_coors = { 0, 10, 502, 240 };

    SDL_RenderCopy(g->renderer, sco_state->sco_texture, &cielo, &horizon_coors);
    SDL_RenderCopy(g->renderer, sco_state->sco_texture, &mountains, &mountain_coors);
    SDL_RenderCopy(g->renderer, sco_state->sco_texture, &tierra, &tierra_coors);
}

void renderPlayer(PlayerState* pla_state, ScenarioState* sco_state, GRAPH* g) {
    static SDL_Rect torso[10];
    static SDL_Rect pierna[6];

    if(pla_state->h >= 0 && pla_state->h < sco_state->floor_coors->count)
        pla_state->y = sco_state->floor_coors->coors[pla_state->h];

    if(pla_state->fullscreen) {
        ToggleFullscreen(g->window);
    }

    switch (pla_state->direction) {
        case DIRECTION_RIGHT:
            if (pla_state->IS_RUNNING_FORWARD) {
                pla_state->indexes = clarkRunV2(g, pla_state, pla_state->animation_arrays);
            } 
            else 
            if (pla_state->isShooting) {
                pla_state->indexes =
                    clarkShootV2(g, pla_state);
            } else {
                pla_state->indexes = clarkStandV2(g, pla_state, *pla_state->animation_arrays);
            }
            break;

        case DIRECTION_LEFT:
            if (pla_state->IS_RUNNING_BACKWARD) {
                pla_state->indexes = clarkRunBackV2(g, pla_state, pla_state->animation_arrays);
            } else {
                pla_state->indexes = clarkStandBackV2(g, pla_state, pla_state->animation_arrays);
            }
            break;
    }

    
}

void renderUpdateCoors(PlayerState* pla_state, ScenarioState* sco_state) {

    //printf("x: %d, h: %d, sco: %d\n", pla_state->x, pla_state->h, sco_state->x);
    const int X_MOUNTAIN_OFFSET = sco_state->X_MOUNTAIN_OFFSET;
    const int X_HORIZON_OFFSET  = sco_state->X_HORIZON_OFFSET;

    if( pla_state->IS_RUNNING_FORWARD ) {
        if( sco_state->x >= sco_state->MAX_WIDTH -1 ) pla_state->sco_end_offset = 80;

        if(pla_state->translate) {
            if( pla_state->x < pla_state->X_RANGE_MAX + pla_state->sco_end_offset ){
                pla_state->x++;
            }else{
                if( sco_state->x < sco_state->MAX_WIDTH ) {
                    sco_state->x++;
                    sco_state->w++;
                    sco_state->x_mountain_offset_counter++;
                }

                if(sco_state->x_mountain_offset_counter >= X_MOUNTAIN_OFFSET) {
                    sco_state->xMountain++;
                }
            }

            if(pla_state->h <= sco_state->floor_coors->count){
                pla_state->h++;
            }
        }     
    }
    
    else
    if( pla_state->IS_RUNNING_BACKWARD ) {
        if(pla_state->translate) {
            if(pla_state->h > 0 && pla_state->x > 0){
                pla_state->x--;
                pla_state->h--;
            }
        }  
        
    } else {
        if(!pla_state->jump && !pla_state->key_shoot){
            pla_state->isRunning = false;
        }
    }


    if(pla_state->breath) pla_state->iTorso++;
    if(pla_state->run) pla_state->iPierna++;

    if( pla_state->iPierna >= pla_state->indexes.iPierna_MAX ) pla_state->iPierna = 0;
    if( pla_state->iTorso  >= pla_state->indexes.iTorso_MAX  ) pla_state->iTorso  = 0;

    if(sco_state->x_mountain_offset_counter >= X_MOUNTAIN_OFFSET)
        sco_state->x_mountain_offset_counter = 0;

    pla_state->breath       = false;
    pla_state->run          = false;
    pla_state->translate    = false;
    pla_state->shoot        = false;
}
