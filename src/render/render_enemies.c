#include "render_enemies.h"
#include "animation_enemies.h"

void renderEnemies(EnemyState* ene_state, GRAPH* g) {
    
    switch(ene_state->mode){
        case MODE_CASUAL_1: {
            ene_state->indexes = soldierCasual(*g, *ene_state);
            break;
        }

        case MODE_SCARED: {
            ene_state->indexes = soldierScared(*g, *ene_state);
            break;
        }
        case MODE_ATTACK: {
            ene_state->indexes = soldierKnifeAttack(*g, *ene_state);
            break;
        }
    }

}

void renderUpdateEnemyCoors( EnemyState* ene_state, PlayerState* pla_state, ScenarioState* sco_state ) {

    ene_state->direction = (pla_state->h < ene_state->h)? DIRECTION_LEFT : DIRECTION_RIGHT;

    if(ene_state->h >= 0 && ene_state->h < sco_state->floor_coors->count)
        ene_state->y = sco_state->floor_coors->coors[ene_state->h] + ene_state->y_offset;


    ///Collision
    if(ene_state->direction == DIRECTION_LEFT) {
        if(pla_state->h + ENEMY_CONTACT == ene_state->h) {
            ene_state->mode = MODE_SCARED;
        }
        else
        if(pla_state->x + ENEMY_CONTACT < ene_state->x){
            ene_state->mode = MODE_CASUAL_1;
        }
    }


    if(ene_state->animate) {
        ene_state->iBody++;
    }

    if(ene_state->iBody >= ene_state->indexes.BODY_MAX -1) {
        ene_state->iBody = 0;

        if(ene_state->mode == MODE_SCARED) {
            ene_state->mode = MODE_ATTACK;
        }
    }

    ene_state->animate = false;
}


void renderEnemyCollisions( EnemyState* ene_state, PlayerState* pla_state, ScenarioState* sco_state ) {
    ///Collision
    if(ene_state->direction == DIRECTION_LEFT) {
        if(pla_state->x + ENEMY_CONTACT == ene_state->x) {
            ene_state->mode = MODE_SCARED;
        }
        else
        if(pla_state->x + ENEMY_CONTACT < ene_state->x){
            ene_state->mode = MODE_CASUAL_1;
        }
    }

}