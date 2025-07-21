#ifndef ANIMATION_H
#define ANIMATION_H

//#include "game.h"
#include <SDL2/SDL.h>
#include <stdbool.h>

enum {
    DIRECTION_LEFT = 1,
    DIRECTION_RIGHT = 2
};

typedef struct {
    short* coors;
    int count;
} FloorCoors;

typedef struct {
    int iTorso_MAX;
    int iPierna_MAX;
} Indexes;

typedef struct {
    SDL_Rect StandTorso[4];
    SDL_Rect StandLegs[1];
    SDL_Rect StandBackTorso[4];
    SDL_Rect StandBackLegs[1];
    SDL_Rect RunTorso[4];
    SDL_Rect RunLegs[6];
    SDL_Rect RunBackTorso[4];
    SDL_Rect RunBackLegs[6];
    SDL_Rect ShootTorso[10];
} AnimationArrays;

typedef struct {
    int x;
    int y;
    int h;
    int iTorso;
    int iPierna;
    int iShoot;
    int x_move_range;
    int X_RANGE_MAX;
    int X_RANGE_MIN;
    int x_displacement;
    int iS;
    int direccion, directionAux;
    bool IS_RUNNING_BACKWARD;
    bool IS_RUNNING_FORWARD;
    bool key_up;
    bool key_down;
    bool run, jump, shoot, breath, translate, key_shoot;
    bool keepWalking, jumpArr;
    bool quit;
    Uint32 pastBreath, pastWalk, pastJump, pastShoot, pastTime;
    bool isRunning;
    bool isShooting;
    int direction;
    int sco_end_offset;
    //FloorCoors* floor_coors;
    Indexes indexes;
    AnimationArrays* animation_arrays;
} PlayerState;

typedef struct{
    SDL_Window* window;
    SDL_Surface* screen;
    SDL_Surface* player;
    SDL_Surface* playerBack;
    SDL_Surface* soldier;
}GRAPH;
//Escenarios
typedef struct{
    SDL_Window* window;
    SDL_Surface* screen;
    SDL_Surface* scenario;
    int x;
    int y;
    int MAX_WIDTH;
    int xMountain;
    int x_mountain_offset_counter;
    int X_MOUNTAIN_OFFSET;
    int xHorizon;
    int x_horizon_offset_counter;
    int X_HORIZON_OFFSET;
    FloorCoors* floor_coors;
} ScenarioState;





// Declaraciones de funciones de animación
Indexes clarkStand(        GRAPH g, int* iT, int* iP, int x, int y, SDL_Rect framesT[], SDL_Rect framesP[]);
Indexes clarkStandBack(    GRAPH g, int iT, int iP, int x, int y, SDL_Rect framesT[], SDL_Rect framesP[]);
Indexes clarkRun(          GRAPH g, int iT, int iP, int x, int y, SDL_Rect framesT[], SDL_Rect framesP[]);
Indexes clarkRunBack(      GRAPH g, int iT, int iP, int x, int y, SDL_Rect framesT[], SDL_Rect framesP[]);
Indexes clarkShoot(        GRAPH g, int* iT, int x, int y, SDL_Rect frames[]);
//Indexes clarkPier(         GRAPH g, int x, int y, SDL_Rect frames[]);

// Definiciones de los arreglos de animaciones
void clarkStandArr(     SDL_Rect torso[4], SDL_Rect pierna[1]);
void clarkStandBackArr( SDL_Rect torso[4], SDL_Rect pierna[1]);
void clarkRunArr(       SDL_Rect torso[4], SDL_Rect pierna[6]);
void clarkRunBackArr(   SDL_Rect torso[4], SDL_Rect pierna[6]);
void clarkShootArr(     SDL_Rect frames[9]);

void clarkUpTorsoArr(SDL_Rect torso[4]);

void initAnimations(AnimationArrays* ani_arrays);
void initClarkAnimations(AnimationArrays* ani_arrays);

/** Updated functions */
Indexes clarkStandV2(GRAPH g, PlayerState pla_state, AnimationArrays ani_arrays);
Indexes clarkStandBackV2(GRAPH g, PlayerState pla_state, AnimationArrays ani_arrays);
Indexes clarkRunV2(GRAPH g, PlayerState* pla_state, AnimationArrays* ani_arrays);
Indexes clarkRunBackV2(GRAPH g, PlayerState* pla_state, AnimationArrays* ani_arrays);

#endif