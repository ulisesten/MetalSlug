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
    int maxTorsoFrames;
    int maxLegsFrames;
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
    int floorIndex;
    int torsoFrame;
    int legsFrame;
    int shootFrame;
    int X_RANGE_MAX;
    int X_RANGE_MIN;
    int x_displacement;
    int direction, lastDirection;
    bool isMovingBackward;
    bool isMovingForward;
    bool shouldBreathe, shouldRun, shouldJump, shouldShoot, shouldTranslate, wantToShoot;
    bool keepWalking, shouldUpdateJump;
    bool quit;
    Uint32 lastBreathTick, lastWalkTick, lastJumpTick, lastShootTick, lastTranslateTick;
    bool isRunning;
    int shotsRemaining;
    int endOfScenarioOffset;
    bool fullscreen;
    Indexes indexes;
    AnimationArrays* animations;
    SDL_Texture* textureFront;
    SDL_Texture* textureBack;
} PlayerState;

typedef struct{
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Surface* screen;
}GRAPH;

//Escenarios
typedef struct{
    SDL_Window* window;
    SDL_Surface* screen;
    SDL_Surface* scenario;
    
    int x;
    int y;
    int w;
    int maxScrollWidth;
    int mountainScrollX;
    int mountainOffsetCounter;
    int MOUNTAIN_SCROLL_RATIO;
    int SCENARIO_END_OFFSET;
    int horizonScrollX;
    int horizonOffsetCounter;
    int HORIZON_SCROLL_RATIO;
    FloorCoors* floor_coors;
    SDL_Texture* sco_texture;
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
Indexes clarkStandV2(       GRAPH* g, PlayerState* pla_state, AnimationArrays ani_arrays);
Indexes clarkStandBackV2(   GRAPH* g, PlayerState* pla_state, AnimationArrays* ani_arrays);
Indexes clarkRunV2(         GRAPH* g, PlayerState* pla_state, AnimationArrays* ani_arrays);
Indexes clarkRunBackV2(     GRAPH* g, PlayerState* pla_state, AnimationArrays* ani_arrays);

#endif