#include "animation_player_clark.h"
#include "../constants/player.h"
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


void clarkStandArr(SDL_Rect torso[4],SDL_Rect pierna[1]){
    torso[0].x=10; torso[0].y=5;//Parado--------------------------
    torso[0].w=35; torso[0].h=35;

    torso[1].x=43; torso[1].y=5;
    torso[1].w=35; torso[1].h=35;

    torso[2].x=76; torso[2].y=5;
    torso[2].w=35; torso[2].h=35;

    torso[3].x=109; torso[3].y=5;
    torso[3].w=35; torso[3].h=35;

    pierna[0].x=145; pierna[0].y=20;
    pierna[0].w=35; pierna[0].h=23;//-----------------------------
}

void clarkStandBackArr(SDL_Rect torso[4],SDL_Rect pierna[1]){
    torso[0].x=710; torso[0].y=5;//Parado--------------------------
    torso[0].w=30; torso[0].h=30;

    torso[1].x=677; torso[1].y=5;
    torso[1].w=30; torso[1].h=30;

    torso[2].x=644; torso[2].y=5;
    torso[2].w=30; torso[2].h=30;

    torso[3].x=611; torso[3].y=5;
    torso[3].w=30; torso[3].h=30;

    pierna[0].x=580; pierna[0].y=20;  pierna[0].w=30; pierna[0].h=23;//-----------------------------
}

void clarkRunArr(SDL_Rect torso[4],SDL_Rect pierna[6]){
    torso[0].x=10; torso[0].y=5;   torso[0].w=35; torso[0].h=35;
    torso[1].x=43; torso[1].y=5;   torso[1].w=35; torso[1].h=35;
    torso[2].x=76; torso[2].y=5;   torso[2].w=35; torso[2].h=35;
    torso[3].x=109; torso[3].y=5;  torso[3].w=35; torso[3].h=35;

    //Corriendo---------------------------------------------------------
    pierna[0].x=13;  pierna[0].y=434; pierna[0].w=34;  pierna[0].h=24;
    pierna[1].x=57;  pierna[1].y=434; pierna[1].w=34;  pierna[1].h=24;
    pierna[2].x=101; pierna[2].y=434; pierna[2].w=34;  pierna[2].h=24;
    pierna[3].x=133; pierna[3].y=434; pierna[3].w=34;  pierna[3].h=24;
    pierna[4].x=167; pierna[4].y=434; pierna[4].w=34;  pierna[4].h=24;
    pierna[5].x=201; pierna[5].y=434; pierna[5].w=34;  pierna[5].h=24;//----------------------------
}

/* Indexes clarkPier(GRAPH g,int x,int y,SDL_Rect pierna[]){
    SDL_Rect pierCoor;

    //pierna.x=580; pierna.y=20;
    //pierna.w=30; pierna.h=30;//-----------------------------

    pierCoor.x=0+x; pierCoor.y=41+y;//Piernas

    SDL_BlitSurface(g.player,&pierna[0],g.screen,&pierCoor);//Clark torzo
    SDL_UpdateWindowSurface(g.window);//Refrescando pantalla
    return (Indexes){1,1};
} */

/* void clarkPiernasRunArr(SDL_Rect torzo[4],SDL_Rect pierna[6]){
    //Corriendo---------------------------------------------------
    pierna[0].x=  13; pierna[0].y=   434;
    pierna[0].w=  34; pierna[0].h=    34;

    pierna[1].x=  57; pierna[1].y=   434;
    pierna[1].w=  34; pierna[1].h=    34;

    pierna[2].x= 101; pierna[2].y=  434;
    pierna[2].w=  34;  pierna[2].h=  34;

    pierna[3].x= 133; pierna[3].y=  434;
    pierna[3].w=  34;  pierna[3].h=  34;

    pierna[4].x= 167; pierna[4].y=  434;
    pierna[4].w=  34;  pierna[4].h=  34;

    pierna[5].x= 201; pierna[5].y=  434;
    pierna[5].w=  34;  pierna[5].h=  34;//----------------------------
} */

void clarkRunBackArr(SDL_Rect torso[4],SDL_Rect pierna[6]){
    //Parado-------------------------------
    torso[0].x=710; torso[0].y=5;
    torso[0].w=30; torso[0].h=30;

    torso[1].x=677; torso[1].y=5;
    torso[1].w=30; torso[1].h=30;

    torso[2].x=644; torso[2].y=5;
    torso[2].w=30; torso[2].h=30;

    torso[3].x=611; torso[3].y=5;
    torso[3].w=30; torso[3].h=30;
    //Corriendo---------------------------------------------------------
    pierna[0].x=711; pierna[0].y=434;  pierna[0].w=34;  pierna[0].h=24;
    pierna[1].x=667; pierna[1].y=434;  pierna[1].w=34;  pierna[1].h=24;
    pierna[2].x=626; pierna[2].y=434;  pierna[2].w=34;  pierna[2].h=24;
    pierna[3].x=591; pierna[3].y=434;  pierna[3].w=34;  pierna[3].h=24;
    pierna[4].x=557; pierna[4].y=434;  pierna[4].w=34;  pierna[4].h=24;
    pierna[5].x=523; pierna[5].y=434;  pierna[5].w=34;  pierna[5].h=24;//----------------------------------
}

void clarkShootArr(SDL_Rect torso[10]){
    torso[0].x=19;   torso[0].y=50;//Disparando adelante------------
    torso[0].w=55;   torso[0].h=30;

    torso[1].x=85;   torso[1].y=50;
    torso[1].w=55;   torso[1].h=30;

    torso[2].x=153;  torso[2].y=50;
    torso[2].w=57;   torso[2].h=30;

    torso[3].x=206;  torso[3].y=50;
    torso[3].w=37;   torso[3].h=30;

    torso[4].x=206;  torso[4].y=50;
    torso[4].w=50;   torso[4].h=30;

    torso[5].x=303;  torso[5].y=50;
    torso[5].w=45;   torso[5].h=30;

    torso[6].x=352;  torso[6].y=50;
    torso[6].w=45;   torso[6].h=30;

    torso[7].x=401;  torso[7].y=48;
    torso[7].w=40;   torso[7].h=30;

    torso[8].x=449;  torso[8].y=49;
    torso[8].w=35;   torso[8].h=30;

    torso[9].x=498;  torso[9].y=50;
    torso[9].w=35;   torso[9].h=30;
}

void clarkShootBackArr(SDL_Rect torso[10]){
    torso[0].x=677;   torso[0].y=50;//Disparando adelante------------
    torso[0].w=55;   torso[0].h=30;// ok

    torso[1].x=611;   torso[1].y=50; // ok
    torso[1].w=55;   torso[1].h=30;

    torso[2].x=543;  torso[2].y=50; // ok
    torso[2].w=57;   torso[2].h=30;

    torso[3].x=490;  torso[3].y=50; // ok
    torso[3].w=53;   torso[3].h=30;

    torso[4].x=441;  torso[4].y=50; // ok
    torso[4].w=53;   torso[4].h=30;

    torso[5].x=393;  torso[5].y=50; // ok
    torso[5].w=52;   torso[5].h=30;

    torso[6].x=344;  torso[6].y=50; // ok
    torso[6].w=52;   torso[6].h=30;

    torso[7].x=295;  torso[7].y=48; // ok
    torso[7].w=52;   torso[7].h=30;

    torso[8].x=247;  torso[8].y=49; // ok
    torso[8].w=52;   torso[8].h=30;

    torso[9].x=295;  torso[9].y=48; // ok
    torso[9].w=52;   torso[9].h=30;
}

void clarkUpTorsoArr(SDL_Rect torso[4]) {
    torso[0].x = 10;  torso[0].y = 85;  torso[0].w = 35;  torso[0].h = 35;
    torso[1].x = 43;  torso[1].y = 85;  torso[1].w = 33;  torso[1].h = 35;
    torso[2].x = 76;  torso[2].y = 85;  torso[2].w = 35;  torso[2].h = 35;
    torso[3].x = 109; torso[3].y = 85;  torso[3].w = 35;  torso[3].h = 35;
}

void clarkUpBackTorsoArr(SDL_Rect torso[4]) {
    torso[0].x = 704;   torso[0].y = 85;
    torso[0].w = 35;    torso[0].h = 35;

    torso[1].x = 671;    torso[1].y = 85;
    torso[1].w = 33;    torso[1].h = 35;

    torso[2].x = 638;    torso[2].y = 85;
    torso[2].w = 35;    torso[2].h = 35;

    torso[3].x = 605;   torso[3].y = 85;
    torso[3].w = 35;    torso[3].h = 35;
}


void clarkJumpTorsoArr(SDL_Rect torso[6]) {
    torso[0].x = 12;  torso[0].y = 635;  torso[0].w = 30;  torso[0].h = 35;
    torso[1].x = 45;  torso[1].y = 635;  torso[1].w = 30;  torso[1].h = 35;
    torso[2].x = 78;  torso[2].y = 635;  torso[2].w = 30;  torso[2].h = 35;
    torso[3].x = 111; torso[3].y = 635;  torso[3].w = 30;  torso[3].h = 35;
    torso[4].x = 144; torso[4].y = 635;  torso[4].w = 30;  torso[4].h = 35;
    torso[5].x = 176; torso[5].y = 635;  torso[5].w = 30;  torso[5].h = 35;
}

void clarkJumpBackTorsoArr(SDL_Rect torso[6]) {
    torso[0].x = 711;  torso[0].y = 635;  torso[0].w = 30;  torso[0].h = 35;
    torso[1].x = 677;  torso[1].y = 635;  torso[1].w = 30;  torso[1].h = 35;
    torso[2].x = 643;  torso[2].y = 635;  torso[2].w = 30;  torso[2].h = 35;
    torso[3].x = 612; torso[3].y =  635;  torso[3].w = 30;  torso[3].h = 35;
    torso[4].x = 579; torso[4].y =  635;  torso[4].w = 30;  torso[4].h = 35;
    torso[5].x = 545; torso[5].y =  635;  torso[5].w = 30;  torso[5].h = 35;
}

void clarkJumpLegsArr(SDL_Rect legs[6]) {
    legs[0].x = 19;  legs[0].y = 670;  legs[0].w = 20;  legs[0].h = 25;
    legs[1].x = 52;  legs[1].y = 670;  legs[1].w = 20;  legs[1].h = 25;
    legs[2].x = 85;  legs[2].y = 670;  legs[2].w = 20;  legs[2].h = 25;
    legs[3].x = 118; legs[3].y = 670;  legs[3].w = 20;  legs[3].h = 25;
    legs[4].x = 150; legs[4].y = 670;  legs[4].w = 20;  legs[4].h = 25;
    legs[5].x = 183; legs[5].y = 670;  legs[5].w = 20;  legs[5].h = 25;
}

void clarkJumpBackLegsArr(SDL_Rect legs[6]) {
    legs[0].x = 715;  legs[0].y = 670;  legs[0].w = 20;  legs[0].h = 25;
    legs[1].x = 681;  legs[1].y = 670;  legs[1].w = 20;  legs[1].h = 25;
    legs[2].x = 647;  legs[2].y = 670;  legs[2].w = 20;  legs[2].h = 25;
    legs[3].x = 614;  legs[3].y = 670;  legs[3].w = 20;  legs[3].h = 25;
    legs[4].x = 581;  legs[4].y = 670;  legs[4].w = 20;  legs[4].h = 25;
    legs[5].x = 548;  legs[5].y = 670;  legs[5].w = 20;  legs[5].h = 25;
}

void clarkDeadByShootArr(SDL_Rect body[19]) {
    body[0].x=8;   body[0].y=4101; body[0].w=32; body[0].h=47;
    body[1].x=38;  body[1].y=4101; body[1].w=32; body[1].h=47;
    body[2].x=70;  body[2].y=4101; body[2].w=32; body[2].h=47;
    body[3].x=108; body[3].y=4101; body[3].w=45; body[3].h=47;
    body[4].x=152; body[4].y=4101; body[4].w=48; body[4].h=47;
    body[5].x=201; body[5].y=4101; body[5].w=48; body[5].h=47;
    body[6].x=250; body[6].y=4101; body[6].w=50; body[6].h=47;
    body[7].x=299; body[7].y=4101; body[7].w=45; body[7].h=47;
    body[8].x=355; body[8].y=4101; body[8].w=39; body[8].h=47;
    body[9].x=398; body[9].y=4101; body[9].w=35; body[9].h=47;
    body[10].x=431;body[10].y=4101;body[10].w=33;body[10].h=47;
    body[11].x=466;body[11].y=4101;body[11].w=48;body[11].h=47;
    body[12].x=513;body[12].y=4101;body[12].w=48;body[12].h=47;
    body[13].x=561;body[13].y=4101;body[13].w=48;body[13].h=39;
    body[14].x=11; body[14].y=4148;body[14].w=49;body[14].h=39;
    body[15].x=62; body[15].y=4148;body[15].w=49;body[15].h=39;
    body[16].x=109;body[16].y=4145;body[16].w=49;body[16].h=44;
    body[17].x=158;body[17].y=4145;body[17].w=49;body[17].h=47;
    body[18].x=208;body[18].y=4145;body[18].w=49;body[18].h=47;
}


void initAnimations(AnimationArrays* ani_arrays) {
    initClarkAnimations(ani_arrays);
    // Aquí puedes agregar más inicializaciones de personajes
}

void initClarkAnimations(AnimationArrays* ani_arrays) {
    clarkStandArr(        ani_arrays->StandTorso,      ani_arrays->StandLegs);
    clarkStandBackArr(    ani_arrays->StandBackTorso,  ani_arrays->StandBackLegs);
    clarkRunArr(          ani_arrays->RunTorso,        ani_arrays->RunLegs);
    clarkRunBackArr(      ani_arrays->RunBackTorso,    ani_arrays->RunBackLegs);
    clarkShootArr(        ani_arrays->ShootTorso);
    clarkShootBackArr(    ani_arrays->ShootBackTorso);
    clarkUpTorsoArr(      ani_arrays->UpTorso);
    clarkUpBackTorsoArr(  ani_arrays->UpBackTorso);
    clarkJumpTorsoArr(    ani_arrays->JumpTorso);
    clarkJumpBackTorsoArr(ani_arrays->JumpBackTorso);
    clarkJumpLegsArr(     ani_arrays->JumpLegs);
    clarkJumpBackLegsArr( ani_arrays->JumpBackLegs);
    clarkDeadByShootArr(  ani_arrays->DeadByShootTorso);
}

/* ====== Per-movement frame setters ====== */

void setStandTorsoFrames(const PlayerState* s, const AnimationArrays* a, int frame, FrameView* v) {
    const bool left = (s->direction == DIRECTION_LEFT);
    const SDL_Rect* arr = left ? a->StandBackTorso : a->StandTorso;
    v->src   = arr[frame];
    v->tex   = left ? s->textureBack : s->textureFront;
    v->off_x = 2;
}

void setRunTorsoFrames(const PlayerState* s, const AnimationArrays* a, int frame, FrameView* v) {
    const bool left = (s->direction == DIRECTION_LEFT);
    const SDL_Rect* arr = left ? a->RunBackTorso : a->RunTorso;
    v->src   = arr[frame];
    v->tex   = left ? s->textureBack : s->textureFront;
    v->off_x = left ? 0 : 2;
}

void setShootTorsoFrames(const PlayerState* s, const AnimationArrays* a, int frame, FrameView* v) {
    const bool left = (s->direction == DIRECTION_LEFT);
    const SDL_Rect* arr = left ? a->ShootBackTorso : a->ShootTorso;
    v->src   = arr[frame];
    v->tex   = left ? s->textureBack : s->textureFront;
    v->off_x = left ? -21 : 2;
}

void setStandLegsFrames(const PlayerState* s, const AnimationArrays* a, FrameView* v) {
    const bool left = (s->direction == DIRECTION_LEFT);
    const SDL_Rect* arr = left ? a->StandBackLegs : a->StandLegs;
    v->src   = arr[0];
    v->tex   = left ? s->textureBack : s->textureFront;
    v->off_x = left ? 9 : 0;
}

void setRunLegsFrames(const PlayerState* s, const AnimationArrays* a, int frame, FrameView* v) {
    const bool left = (s->direction == DIRECTION_LEFT);
    const SDL_Rect* arr = left ? a->RunBackLegs : a->RunLegs;
    v->src   = arr[frame];
    v->tex   = left ? s->textureBack : s->textureFront;
    v->off_x = left ? 7 : 0;
}

void setUpTorsoFrames(const PlayerState* s, const AnimationArrays* a, int frame, FrameView* v) {
    const bool left = (s->direction == DIRECTION_LEFT);
    const SDL_Rect* arr = left ? a->UpBackTorso : a->UpTorso;
    v->src   = arr[frame];
    v->tex   = left ? s->textureBack : s->textureFront;
    v->off_x = left ? -4 : 2;
}

void setJumpTorsoFrames(const PlayerState* s, const AnimationArrays* a, int frame, FrameView* v) {
    const bool left = (s->direction == DIRECTION_LEFT);
    const SDL_Rect* arr = left ? a->JumpBackTorso : a->JumpTorso;
    v->src   = arr[frame];
    v->tex   = left ? s->textureBack : s->textureFront;
    v->off_x = 0;
}

void setJumpLegsFrames(const PlayerState* s, const AnimationArrays* a, int frame, FrameView* v) {
    const bool left = (s->direction == DIRECTION_LEFT);
    const SDL_Rect* arr = left ? a->JumpBackLegs : a->JumpLegs;
    v->src   = arr[frame];
    v->tex   = left ? s->textureBack : s->textureFront;
    v->off_x = 6;
}

void setDeadByShootFrames(const PlayerState* s, const AnimationArrays* a, int frame, FrameView* v) {
    /* Death-by-enemy-melee: single strip, no direction variant. It uses the
     * front-facing texture (player has likely been hit while standing/jumping
     * in some direction, but the death sprite is shared). */
    const int idx = (frame >= PLAYER_DEAD_FRAMES) ? (PLAYER_DEAD_FRAMES - 1) : frame;
    v->src   = a->DeadByShootTorso[idx];
    v->tex   = s->textureFront;
    v->off_x = 0;
}

/* ====== Centralized player animation ====== */

Indexes animate_clark(GRAPH* g, ScenarioState* sco_state, PlayerState* pla_state, AnimationArrays* ani_arrays) {
    FrameView torso, legs;
    int x = pla_state->x;
    int y = pla_state->y;  /* renderPlayer has already applied the jump offset */
    const bool facing_left = (pla_state->direction == DIRECTION_LEFT);
    const bool moving = facing_left ? pla_state->isMovingBackward
                                    : pla_state->isMovingForward;
    const bool jumping = pla_state->shouldJump;
    const bool shooting = (pla_state->shotsRemaining > 0);  /* torso is in shoot cycle */
    int frame_idx;

    /* ====== TORSO (prioridad: death > shoot > jump > lookUp > run > stand) ====== */
    if (pla_state->shouldDie || pla_state->isDead) {
        /* Death animation overrides every other state. While isDead is true
         * the setter clamps the frame to the last index, so the player
         * simply lingers on the last sprite. */
        frame_idx = pla_state->deadFrame;
        setDeadByShootFrames(pla_state, ani_arrays, frame_idx, &torso);

        if (pla_state->shouldAdvanceDeathAnim && !pla_state->isDead) {
            pla_state->deadFrame++;
            if (pla_state->deadFrame >= PLAYER_DEAD_FRAMES) {
                pla_state->deadFrame   = PLAYER_DEAD_FRAMES - 1;
                pla_state->isDead      = true;
                pla_state->shouldDie   = false;
            }
            pla_state->shouldAdvanceDeathAnim = false;
        }
    } else if (pla_state->shotsRemaining > 0) {
        frame_idx = pla_state->shootFrame;
        setShootTorsoFrames(pla_state, ani_arrays, frame_idx, &torso);

        if (pla_state->shouldShoot) {
            pla_state->shootFrame++;
            if (pla_state->shootFrame >= 10) {
                pla_state->shootFrame = 0;
                pla_state->shotsRemaining = 0;
            }
        }
    } else if (jumping) {
        /* Sprite animation cycles independently of trajectory */
        frame_idx = pla_state->jumpAnimFrame % 6;
        setJumpTorsoFrames(pla_state, ani_arrays, frame_idx, &torso);
    } else if (pla_state->shouldLookUp) {
        frame_idx = pla_state->torsoFrame;
        setUpTorsoFrames(pla_state, ani_arrays, frame_idx, &torso);
    } else if (moving) {
        frame_idx = pla_state->torsoFrame;
        setRunTorsoFrames(pla_state, ani_arrays, frame_idx, &torso);
    } else {
        frame_idx = pla_state->torsoFrame;
        setStandTorsoFrames(pla_state, ani_arrays, frame_idx, &torso);
    }

    /* ====== PIERNAS (prioridad: death > jump > run > stand; shoot no las afecta) ====== */
    if (pla_state->shouldDie || pla_state->isDead) {
        /* Keep legs on the standing frame so the death pose looks anchored. */
        setStandLegsFrames(pla_state, ani_arrays, &legs);
    } else if (jumping) {
        setJumpLegsFrames(pla_state, ani_arrays, pla_state->jumpAnimFrame % 6, &legs);
    } else if (moving) {
        setRunLegsFrames(pla_state, ani_arrays, pla_state->legsFrame, &legs);
    } else {
        setStandLegsFrames(pla_state, ani_arrays, &legs);
    }

    /* ====== Build destination rects ====== */
    /* Jump torso sits PLAYER_JUMP_TORSO_Y_OFFSET px lower to correct the
     * sprite desync with the legs. */
    const int torso_y = jumping ? (PLAYER_TORSO_Y_OFFSET + y + PLAYER_JUMP_TORSO_Y_OFFSET)
                                : (PLAYER_TORSO_Y_OFFSET + y);

    int torso_x = x;  /* default torso X position */

    torso_x = jumping && !facing_left ? (torso_x - PLAYER_JUMP_TORSO_X_OFFSET)
                                : x;

    torso_x = jumping && facing_left ? (torso_x + PLAYER_JUMP_TORSO_LEFT_X_OFFSET)
                                : torso_x;

    torso_x = (jumping && shooting && !facing_left)
                          ? (torso_x + PLAYER_JUMB_SHOOTING_TORSO_X_OFFSET)
                          : torso_x;

    /* When jumping + shooting while facing left, the combined sprite is
     * shifted relative to the regular jump pose. Nudge the torso in X. */
    torso_x = (jumping && shooting && facing_left)
                          ? (torso_x - PLAYER_JUMB_SHOOTING_TORSO_LEFT_X_OFFSET)
                          : torso_x;

    SDL_Rect torso_coors = { torso.off_x + torso_x, torso_y, torso.src.w, torso.src.h };

    /* During the death animation the torso sprite already depicts the full
     * collapsed body, so the legs would be drawn redundantly on top of it.
     * Park them off-screen (way outside the logical viewport). */
    SDL_Rect leg_coors;
    if (pla_state->shouldDie || pla_state->isDead) {
        leg_coors.x = -10000;
        leg_coors.y = -10000;
        leg_coors.w = legs.src.w;
        leg_coors.h = legs.src.h;
    } else {
        leg_coors.x = legs.off_x + x;
        leg_coors.y = PLAYER_LEGS_Y_OFFSET + y;
        leg_coors.w = legs.src.w;
        leg_coors.h = legs.src.h;
    }

    SDL_RenderCopy(g->renderer, legs.tex,  &legs.src,  &leg_coors);
    SDL_RenderCopy(g->renderer, torso.tex, &torso.src, &torso_coors);

    /* Cache final destination rects on the player state so the caller can
     * draw debug outlines (collision visualisation) or AABB checks. */
    pla_state->lastTorsoDstRect = torso_coors;
    pla_state->lastLegsDstRect  = leg_coors;

    /* ====== Frame advancing — timers are independent =============
     *  JUMP_ANIM_INTERVAL_MS (sprite cycle, ~80ms)
     *  JUMP_TRAJECTORY_INTERVAL_MS (parabola advance, ~30ms)         */
    if (pla_state->shouldBreathe && pla_state->shotsRemaining == 0 && !jumping) pla_state->torsoFrame++;
    if (pla_state->shouldRun && !jumping) pla_state->legsFrame++;

    if (jumping) {
        if (pla_state->shouldAdvanceJumpAnim) {
            pla_state->jumpAnimFrame++;
        }
        if (pla_state->shouldAdvanceJumpTrajectory && sco_state) {
            pla_state->jumpTrajectoryFrame++;
            /* End jump once the parabolic trajectory completes */
            if (pla_state->jumpTrajectoryFrame >= sco_state->jumpOffsetsCount) {
                pla_state->jumpTrajectoryFrame = 0;
                pla_state->jumpAnimFrame       = 0;
                pla_state->shouldJump          = false;
            }
        }
    }

    const int torso_max = (pla_state->shotsRemaining > 0) ? 10 : (jumping ? 6 : 4);
    if (pla_state->torsoFrame >= torso_max) pla_state->torsoFrame = 0;

    const int legs_max = jumping ? 6 : (moving ? 6 : 1);
    if (pla_state->legsFrame >= legs_max) pla_state->legsFrame = 0;

    return (Indexes){torso_max, legs_max};
}