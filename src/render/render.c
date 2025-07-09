// render.c
#include "render.h"
#include <SDL2/SDL.h>
#include "animation.h"
#include "floor.h"

void renderScenario(ScenarioState* sco_state) {
    SDL_Rect cielo = { 10 + sco_state->xHorizon, 408, 502 + sco_state->xHorizon, 112 };
    SDL_Rect tierraLejana = { 10 + sco_state->xMountain, 560, 502 + sco_state->xMountain, 168 };
    SDL_Rect coorTieLej = { 0, 57, 0, 0 };
    SDL_Rect tierra = { 10 + sco_state->x, sco_state->y, 502 + sco_state->x, 250 };

    SDL_BlitSurface(sco_state->scenario, &cielo, sco_state->screen, NULL);
    SDL_BlitSurface(sco_state->scenario, &tierraLejana, sco_state->screen, &coorTieLej);
    SDL_BlitSurface(sco_state->scenario, &tierra, sco_state->screen, NULL);
}

void renderPlayer(PlayerState* pla_state, GRAPH* g) {
    static SDL_Rect torso[10];
    static SDL_Rect pierna[6];

    if(pla_state->h >= 0 && pla_state->h < pla_state->floor_coors->count)
        pla_state->y = pla_state->floor_coors->coors[pla_state->h];

    switch (pla_state->direction) {
        case DIRECTION_RIGHT:
            if (pla_state->isRunning) {
                pla_state->indexes = clarkRunV2(*g, pla_state, pla_state->animation_arrays);
            } else if (pla_state->isShooting) {
                clarkShootArr(torso);
                pla_state->indexes =
                    clarkShoot(*g, &pla_state->iTorso, pla_state->x, pla_state->y, torso);
            } else {
                clarkStandArr(torso, pierna);
                pla_state->indexes =
                    clarkStand(*g, &pla_state->iTorso, &pla_state->iPierna, pla_state->x, pla_state->y, torso, pierna);
            }
            break;

        case DIRECTION_LEFT:
            if (pla_state->isRunning) {
                pla_state->indexes = clarkRunBackV2(*g, pla_state, pla_state->animation_arrays);
            } else {
                clarkStandBackArr(torso, pierna);
                pla_state->indexes =
                    clarkStandBack(*g, pla_state->iTorso, pla_state->iPierna, pla_state->x, pla_state->y, torso, pierna);
            }
            break;
    }

    
}

void renderUpdateCoors(PlayerState* pla_state, ScenarioState* sco_state) {

    printf("x: %d, h: %d, sco: %d\n", pla_state->x, pla_state->h, sco_state->x);

    if(pla_state->key_right || (pla_state->jump && pla_state->keepWalking && pla_state->directionAux == DIRECTION_RIGHT)){
        
        if(!pla_state->jump) pla_state->isRunning = true;

        if( sco_state->x >= sco_state->MAX_WIDTH -1 ) pla_state->sco_end_offset = 80;

        if(pla_state->translate) {
            if( pla_state->x < pla_state->X_RANGE_MAX + pla_state->sco_end_offset ){
                pla_state->x++;
            }else{
                if( sco_state->x < sco_state->MAX_WIDTH ) {

                    sco_state->x++;
                    sco_state->x_mountain_offset++;
                }

                if(sco_state->x_mountain_offset >= 4) {
                    sco_state->xMountain++;
                }
            }

            if(pla_state->h <= pla_state->floor_coors->count){
                pla_state->h++;
            }
        }
                
    } else if(pla_state->key_left || (pla_state->jump && pla_state->keepWalking && pla_state->directionAux == DIRECTION_LEFT)){
        
        if(!pla_state->jump) pla_state->isRunning = true;

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

    if(sco_state->x_mountain_offset >= 4) sco_state->x_mountain_offset = 0;

    pla_state->breath       = false;
    pla_state->run          = false;
    pla_state->translate    = false;
    pla_state->shoot        = false;
}
