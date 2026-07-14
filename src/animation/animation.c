#include "animation.h"
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
    pierna[0].w=35; pierna[0].h=34;//-----------------------------
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

    pierna[0].x=580; pierna[0].y=20;
    pierna[0].w=30; pierna[0].h=30;//-----------------------------
}

void clarkRunArr(SDL_Rect torso[4],SDL_Rect pierna[6]){
    torso[0].x=10; torso[0].y=5;//Parado--------------------------
    torso[0].w=35; torso[0].h=35;

    torso[1].x=43; torso[1].y=5;
    torso[1].w=35; torso[1].h=35;

    torso[2].x=76; torso[2].y=5;
    torso[2].w=35; torso[2].h=35;

    torso[3].x=109; torso[3].y=5;
    torso[3].w=35; torso[3].h=35;
            //Corriendo---------------------------------------------------------
    pierna[0].x=13; pierna[0].y=434;
    pierna[0].w=34; pierna[0].h=34;

    pierna[1].x=57; pierna[1].y=434;
    pierna[1].w=34; pierna[1].h=34;

    pierna[2].x=101; pierna[2].y=434;
    pierna[2].w=34;  pierna[2].h=34;

    pierna[3].x=133; pierna[3].y=434;
    pierna[3].w=34;  pierna[3].h=34;

    pierna[4].x=167; pierna[4].y=434;
    pierna[4].w=34;  pierna[4].h=34;

    pierna[5].x=201; pierna[5].y=434;
    pierna[5].w=34;  pierna[5].h=34;//----------------------------
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
    pierna[0].x=711; pierna[0].y=434;
    pierna[0].w=34; pierna[0].h=34;

    pierna[1].x=667; pierna[1].y=434;
    pierna[1].w=34; pierna[1].h=34;

    pierna[2].x=626; pierna[2].y=434;
    pierna[2].w=34;  pierna[2].h=34;

    pierna[3].x=591; pierna[3].y=434;
    pierna[3].w=34;  pierna[3].h=34;

    pierna[4].x=557; pierna[4].y=434;
    pierna[4].w=34;  pierna[4].h=34;

    pierna[5].x=523; pierna[5].y=434;
    pierna[5].w=34;  pierna[5].h=34;//----------------------------------
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

void initAnimations(AnimationArrays* ani_arrays) {
    initClarkAnimations(ani_arrays);
    // Aquí puedes agregar más inicializaciones de personajes
}

void initClarkAnimations(AnimationArrays* ani_arrays) {
    clarkStandArr(      ani_arrays->StandTorso,      ani_arrays->StandLegs);
    clarkStandBackArr(  ani_arrays->StandBackTorso,  ani_arrays->StandBackLegs);
    clarkRunArr(        ani_arrays->RunTorso,        ani_arrays->RunLegs);
    clarkRunBackArr(    ani_arrays->RunBackTorso,    ani_arrays->RunBackLegs);
    clarkShootArr(      ani_arrays->ShootTorso);
    clarkShootBackArr(  ani_arrays->ShootBackTorso);
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

/* ====== Centralized player animation ====== */

Indexes animate_clark(GRAPH* g, PlayerState* pla_state, AnimationArrays* ani_arrays) {
    FrameView torso, legs;
    const int x = pla_state->x;
    const int y = pla_state->y;
    const bool facing_left = (pla_state->direction == DIRECTION_LEFT);
    const bool moving = facing_left ? pla_state->isMovingBackward
                                    : pla_state->isMovingForward;
    int frame_idx;

    /* ====== TORSO ====== */
    if (pla_state->shotsRemaining > 0) {
        frame_idx = pla_state->shootFrame;
        setShootTorsoFrames(pla_state, ani_arrays, frame_idx, &torso);

        if (pla_state->shouldShoot) {
            pla_state->shootFrame++;
            if (pla_state->shootFrame >= 10) {
                pla_state->shootFrame = 0;
                pla_state->shotsRemaining = 0;
            }
        }
    } else if (moving) {
        frame_idx = pla_state->torsoFrame;
        setRunTorsoFrames(pla_state, ani_arrays, frame_idx, &torso);
    } else {
        frame_idx = pla_state->torsoFrame;
        setStandTorsoFrames(pla_state, ani_arrays, frame_idx, &torso);
    }

    /* ====== PIERNAS (independientes del disparo) ====== */
    if (moving) {
        setRunLegsFrames(pla_state, ani_arrays, pla_state->legsFrame, &legs);
    } else {
        setStandLegsFrames(pla_state, ani_arrays, &legs);
    }

    /* ====== Build destination rects ====== */
    SDL_Rect torso_coors = { torso.off_x + x, 20 + y, torso.src.w, torso.src.h };
    SDL_Rect leg_coors   = { legs.off_x  + x, 41 + y, legs.src.w,  legs.src.h  };

    SDL_RenderCopy(g->renderer, legs.tex,  &legs.src,  &leg_coors);
    SDL_RenderCopy(g->renderer, torso.tex, &torso.src, &torso_coors);

    /* ====== Frame advancing ====== */
    if (pla_state->shouldBreathe && pla_state->shotsRemaining == 0) pla_state->torsoFrame++;
    if (pla_state->shouldRun) pla_state->legsFrame++;

    const int torso_max = (pla_state->shotsRemaining > 0) ? 10 : 4;
    if (pla_state->torsoFrame >= torso_max) pla_state->torsoFrame = 0;

    const int legs_max = moving ? 6 : 1;
    if (pla_state->legsFrame >= legs_max) pla_state->legsFrame = 0;

    return (Indexes){torso_max, legs_max};
}