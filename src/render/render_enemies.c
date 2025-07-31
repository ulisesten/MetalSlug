#include "render_enemies.h"
#include "animation_enemies.h"

void renderEnemies(EnemyState* ene_state, GRAPH* g) {
    
    switch(ene_state->mode){
        case MODE_CASUAL_1: {
            ene_state->indexes = soldierCasual(g, *ene_state, ene_state->direction);
            break;
        }

        case MODE_SCARED: {
            ene_state->indexes = soldierScared(g, *ene_state, ene_state->direction);
            break;
        }
        case MODE_PURSUIT: {
            ene_state->indexes = soldierPursuit(g, *ene_state, ene_state->direction);
            break;
        }
        case MODE_ATTACK: {
            ene_state->indexes = soldierKnifeAttack(g, *ene_state, ene_state->direction);
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
        if(     pla_state->h + ENEMY_CLOSE == ene_state->h
            &&  !(ene_state->isOperating)) {
            ene_state->mode = MODE_SCARED;
        }

        if(ene_state->mode == MODE_PURSUIT && ene_state->walk){
            ene_state->x--;
            ene_state->h--;
            ene_state->free_animation = true;
        }
    }

    else
    if(ene_state->direction == DIRECTION_RIGHT) {
        if(ene_state->mode == MODE_PURSUIT && ene_state->walk){
            ene_state->x++;
            ene_state->h++;
            ene_state->free_animation = true;
        }

    }


    if(ene_state->animate) {
        ene_state->iBody++;
    }

    if(ene_state->iBody > ene_state->indexes.BODY_MAX -1) {
        ene_state->iBody = 0;
        ene_state->free_animation = true;

        if(ene_state->mode == MODE_SCARED) {
            ene_state->isOperating = true;
        }
    }

    ene_state->animate = false;
    ene_state->walk = false;
}


void renderEnemyCollisions( EnemyState* ene_state, PlayerState* pla_state, ScenarioState* sco_state ) {
    ///Collision
    if(ene_state->direction == DIRECTION_LEFT && ene_state->free_animation) {

        if(     ene_state->isOperating
            ||  pla_state->x + ENEMY_CLOSE < ene_state->x && ene_state->mode != MODE_CASUAL_1){
            
            ene_state->mode = MODE_PURSUIT;
            ene_state->free_animation = false;

        }
        
        if(     pla_state->x >= ene_state->x - ENEMY_CONTACT
            &&  pla_state->x <= ene_state->x + ENEMY_CONTACT ){

            ene_state->mode = MODE_ATTACK;
            ene_state->free_animation = false;

        }

        if(pla_state->x + ENEMY_CLOSE == ene_state->x) {

            ene_state->mode = MODE_SCARED;
            ene_state->free_animation = false;

        }
        else
        if(pla_state->x + ENEMY_CLOSE < ene_state->x){

            ene_state->mode = MODE_CASUAL_1;
            ene_state->free_animation = false;

        }
    }
    else
    if(ene_state->direction == DIRECTION_RIGHT && ene_state->free_animation) {
        if(     ene_state->isOperating
            ||  pla_state->x - ENEMY_CLOSE > ene_state->x && ene_state->mode != MODE_CASUAL_1){
            
            ene_state->mode = MODE_PURSUIT;
            ene_state->free_animation = false;

        }
    }

}