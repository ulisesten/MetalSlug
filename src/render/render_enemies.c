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

    ene_state->direction = (pla_state->floorIndex < ene_state->floorIndex)? DIRECTION_LEFT : DIRECTION_RIGHT;

    if(ene_state->floorIndex >= 0 && ene_state->floorIndex < sco_state->floor_coors->count)
        ene_state->y = sco_state->floor_coors->coors[ene_state->floorIndex] + ene_state->spriteVerticalOffset;

    ene_state->scenarioScrollOffset = sco_state->x;

    ///Collision
    if(ene_state->direction == DIRECTION_LEFT) {
        if(     pla_state->floorIndex + ENEMY_CLOSE_DISTANCE == ene_state->floorIndex
            &&  !(ene_state->hasReacted)) {
            ene_state->mode = MODE_SCARED;
        }

        if(ene_state->mode == MODE_PURSUIT && ene_state->shouldWalk){
            ene_state->x--;
            ene_state->floorIndex--;
            ene_state->canTransitionMode = true;
        }
    }

    else
    if(ene_state->direction == DIRECTION_RIGHT) {
        if(ene_state->mode == MODE_PURSUIT && ene_state->shouldWalk){
            ene_state->x++;
            ene_state->floorIndex++;
            ene_state->canTransitionMode = true;
        }

    }


    if(ene_state->shouldAnimate) {
        ene_state->bodyFrame++;
    }

    if(ene_state->bodyFrame > ene_state->indexes.maxBodyFrames -1) {
        ene_state->bodyFrame = 0;
        ene_state->canTransitionMode = true;

        if(ene_state->mode == MODE_SCARED) {
            ene_state->hasReacted = true;
        }
    }

    ene_state->shouldAnimate = false;
    ene_state->shouldWalk = false;
}


void renderEnemyCollisions( EnemyState* ene_state, PlayerState* pla_state, ScenarioState* sco_state ) {
    ///Collision
    if(ene_state->direction == DIRECTION_LEFT && ene_state->canTransitionMode) {

        if(     ene_state->hasReacted
            ||  pla_state->floorIndex + ENEMY_CLOSE_DISTANCE < ene_state->floorIndex && ene_state->mode != MODE_CASUAL_1){
            
            ene_state->mode = MODE_PURSUIT;
            ene_state->canTransitionMode = false;

        }
        
        if(     pla_state->floorIndex >= ene_state->floorIndex - ENEMY_CONTACT_DISTANCE
            &&  pla_state->floorIndex <= ene_state->floorIndex + ENEMY_CONTACT_DISTANCE ){

            ene_state->mode = MODE_ATTACK;
            ene_state->canTransitionMode = false;

        }

        if(pla_state->floorIndex + ENEMY_CLOSE_DISTANCE == ene_state->floorIndex) {

            ene_state->mode = MODE_SCARED;
            ene_state->canTransitionMode = false;

        }
        else
        if(pla_state->floorIndex + ENEMY_CLOSE_DISTANCE < ene_state->floorIndex){

            ene_state->mode = MODE_CASUAL_1;
            ene_state->canTransitionMode = false;

        }
    }
    else
    if(ene_state->direction == DIRECTION_RIGHT && ene_state->canTransitionMode) {
        if(     ene_state->hasReacted
            ||  pla_state->floorIndex - ENEMY_CLOSE_DISTANCE > ene_state->floorIndex && ene_state->mode != MODE_CASUAL_1){
            
            ene_state->mode = MODE_PURSUIT;
            ene_state->canTransitionMode = false;

        }
    }

}
