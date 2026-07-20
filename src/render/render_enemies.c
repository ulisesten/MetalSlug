#include "render_enemies.h"
#include "animation_enemies.h"
#include "../constants/player.h"

void renderEnemies(EnemyState* ene_state, GRAPH* g) {
    /* isDead = instant death (unused for now). isDying = playing death anim.
     * isBlinking = post-death blink. shouldRemove = cleaned up in game loop. */
    if (ene_state->isDead || ene_state->shouldRemove) {
        ene_state->indexes = (EnemyIndexes){0};
        return;
    }

    if (ene_state->isDying) {
        /* Death-by-bullet animation overrides mode. */
        ene_state->bodyFrame = ene_state->deadFrame;
        ene_state->indexes = soldierDeadByShoot(g, *ene_state, ene_state->direction, &ene_state->lastBodyDstRect);
        return;
    }

    if (ene_state->isBlinking) {
        /* Blink: draw every other ENEMY_BLINK_INTERVAL_MS. We still call the
         * mode renderer but skip the actual RenderCopy when "off". */
        const int blink_idx = ene_state->blinkFrame % (ENEMY_BLINK_FRAMES * 2);
        const bool visible = (blink_idx < ENEMY_BLINK_FRAMES);
        if (!visible) {
            ene_state->indexes = (EnemyIndexes){0};
            return;
        }
        /* Fall through to render current mode while visible. */
    }

    SDL_Rect* cache = &ene_state->lastBodyDstRect;
    switch(ene_state->mode){
        case MODE_CASUAL_1: {
            ene_state->indexes = soldierCasual(g, *ene_state, ene_state->direction, cache);
            break;
        }

        case MODE_SCARED: {
            ene_state->indexes = soldierScared(g, *ene_state, ene_state->direction, cache);
            break;
        }
        case MODE_PURSUIT: {
            ene_state->indexes = soldierPursuit(g, *ene_state, ene_state->direction, cache);
            break;
        }
        case MODE_ATTACK: {
            ene_state->indexes = soldierKnifeAttack(g, *ene_state, ene_state->direction, cache);
            break;
        }
    }

}

void renderUpdateEnemyCoors( EnemyState* ene_state, PlayerState* pla_state, ScenarioState* sco_state ) {

    /* During death/blink/remove phases we still track scenario scroll so
     * the corpse stays anchored to the world (the player can keep
     * scrolling past it); we just skip all personal movement and mode
     * transitions. */
    if (ene_state->isDead || ene_state->isDying
        || ene_state->isBlinking || ene_state->shouldRemove) {
        ene_state->scenarioScrollOffset = sco_state->x;
        return;
    }

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
    /* Dead/dying/being-removed enemies don't interact. Also, once the
     * player is dead we stop driving the enemy state machine so their
     * mode stays where it is (otherwise MODE_ATTACK would be re-set
     * every frame and the corpse's animation would never settle). */
    if (ene_state->isDead || ene_state->isDying
        || ene_state->isBlinking || ene_state->shouldRemove) return;
    if (pla_state->isDead) return;

    /* X-axis proximity — the candidate contact window. */
    const bool in_x_range =
        (pla_state->floorIndex >= ene_state->floorIndex - ENEMY_CONTACT_DISTANCE)
        && (pla_state->floorIndex <= ene_state->floorIndex + ENEMY_CONTACT_DISTANCE);

    /* Y-axis safety check: when the player is jumping, only ground-level
     * contact (within the enemy's reach) kills. Above PLAYER_AIRBORNE_THRESHOLD,
     * the player's sprite is too high up for a ground soldier to hit. */
    bool airborne_clear = false;
    if (pla_state->shouldJump && sco_state && sco_state->jumpOffsetsCount > 0) {
        int idx = pla_state->jumpTrajectoryFrame;
        if (idx < 0) idx = 0;
        if (idx >= sco_state->jumpOffsetsCount) idx = sco_state->jumpOffsetsCount - 1;
        airborne_clear = (sco_state->jumpOffsets[idx] >= PLAYER_AIRBORNE_THRESHOLD);
    }

    if (in_x_range && !airborne_clear) {
        /* Enemy melee kills the player (edge-triggered so we don't keep
         * re-setting shouldDie after isDead is already true). */
        if (!pla_state->shouldDie && !pla_state->isDead) {
            pla_state->shouldDie = true;
        }
        /* Force the enemy into attack pose (visual only) and keep it there. */
        ene_state->mode = MODE_ATTACK;
        ene_state->canTransitionMode = false;
        return;
    }

    ///Collision (mode transitions when not in contact)
    if(ene_state->direction == DIRECTION_LEFT && ene_state->canTransitionMode) {

        if(     ene_state->hasReacted
            ||  pla_state->floorIndex + ENEMY_CLOSE_DISTANCE < ene_state->floorIndex && ene_state->mode != MODE_CASUAL_1){
            
            ene_state->mode = MODE_PURSUIT;
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
