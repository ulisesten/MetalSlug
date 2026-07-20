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
    SDL_Rect ShootBackTorso[10];
    SDL_Rect UpTorso[4];
    SDL_Rect UpBackTorso[4];
    SDL_Rect JumpTorso[6];
    SDL_Rect JumpBackTorso[6];
    SDL_Rect JumpLegs[6];
    SDL_Rect JumpBackLegs[6];
    SDL_Rect DeadByShootTorso[19]; /* death-by-enemy-melee sprite strip */
} AnimationArrays;

typedef struct {
    int x;
    int y;
    int floorIndex;
    int torsoFrame;
    int legsFrame;
    int shootFrame;
    int jumpAnimFrame;        /* sprite animation cycling 6 frames */
    int jumpTrajectoryFrame;  /* parabolic trajectory index (0..jumpOffsetsCount-1) */
    int deadFrame;            /* index into clarkDeadByShoot (0..PLAYER_DEAD_FRAMES-1) */
    int X_RANGE_MAX;
    int X_RANGE_MIN;
    int x_displacement;
    int direction, lastDirection;
    bool isMovingBackward;
    bool isMovingForward;
    bool shouldBreathe, shouldRun, shouldJump, shouldShoot, shouldTranslate, wantToShoot, shouldLookUp;
    bool keepWalking, shouldAdvanceJumpAnim, shouldAdvanceJumpTrajectory;
    bool shouldAdvanceDeathAnim;
    bool pendingShot;            /* edge-triggered manual shot request */
    bool shouldDie;              /* edge-triggered death-by-enemy-melee */
    bool isDead;                 /* death animation has finished; linger on last frame */
    bool quit;
    Uint32 lastBreathTick, lastWalkTick, lastJumpAnimTick, lastJumpTrajectoryTick, lastShootTick, lastTranslateTick, lastDeadTick;
    Uint32 lastBulletShotMs;     /* timestamp of last bullet fired (for cooldown) */
    bool isRunning;
    int shotsRemaining;
    int endOfScenarioOffset;
    bool fullscreen;
    Indexes indexes;
    AnimationArrays* animations;
    SDL_Texture* textureFront;
    SDL_Texture* textureBack;
    /* Debug — destination rects last frame, exposed for collision visualisation. */
    SDL_Rect lastTorsoDstRect;
    SDL_Rect lastLegsDstRect;
    SDL_Rect lastCollisionRect; /* compact AABB (torso+legs) used for collisions */
    bool showDebugRects;        /* toggled by F1; outlines sprites when true */
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
    int jumpOffsets[52]; /* parabolic jump trajectory (pixels up) */
    int jumpOffsetsCount;
} ScenarioState;


// Definiciones de los arreglos de animaciones
void clarkStandArr(     SDL_Rect torso[4], SDL_Rect pierna[1]);
void clarkStandBackArr( SDL_Rect torso[4], SDL_Rect pierna[1]);
void clarkRunArr(       SDL_Rect torso[4], SDL_Rect pierna[6]);
void clarkRunBackArr(   SDL_Rect torso[4], SDL_Rect pierna[6]);
void clarkShootArr(     SDL_Rect torso[10]);
void clarkShootBackArr( SDL_Rect torso[10]);

void clarkUpTorsoArr(   SDL_Rect torso[4]);
void clarkUpBackTorsoArr(SDL_Rect torso[4]);
void clarkJumpTorsoArr(   SDL_Rect torso[6]);
void clarkJumpBackTorsoArr(SDL_Rect torso[6]);
void clarkJumpLegsArr(    SDL_Rect legs[6]);
void clarkJumpBackLegsArr(SDL_Rect legs[6]);
void clarkDeadByShootArr( SDL_Rect torso[19]);

void initAnimations(AnimationArrays* ani_arrays);
void initClarkAnimations(AnimationArrays* ani_arrays);

/**
 * Frame view: source rect, texture and destination offset selected by the
 * setter helpers. animate_clark composes one for torso and one for legs.
 */
typedef struct {
    SDL_Rect     src;
    SDL_Texture*  tex;
    int           off_x;
} FrameView;

/* Per-movement setters. They pick the right sprite strip and texture for the
 * given direction (DIRECTION_LEFT uses the *Back* variants), then write the
 * computed FrameView (caller still adds pla_state->x/y). */
void setStandTorsoFrames(  const PlayerState* s, const AnimationArrays* a, int frame, FrameView* v);
void setRunTorsoFrames(    const PlayerState* s, const AnimationArrays* a, int frame, FrameView* v);
void setShootTorsoFrames(  const PlayerState* s, const AnimationArrays* a, int frame, FrameView* v);
void setStandLegsFrames(   const PlayerState* s, const AnimationArrays* a,             FrameView* v);
void setRunLegsFrames(     const PlayerState* s, const AnimationArrays* a, int frame, FrameView* v);
void setUpTorsoFrames(     const PlayerState* s, const AnimationArrays* a, int frame, FrameView* v);
void setJumpTorsoFrames(   const PlayerState* s, const AnimationArrays* a, int frame, FrameView* v);
void setJumpLegsFrames(    const PlayerState* s, const AnimationArrays* a, int frame, FrameView* v);
void setDeadByShootFrames( const PlayerState* s, const AnimationArrays* a, int frame, FrameView* v);

/**
 * @brief Centralized player renderer + frame advancing.
 *
 * Handles torso and legs independently so new state combinations
 * (e.g. running + shooting) can be added by changing the torso branch
 * without duplicating legs logic. Advances torsoFrame/legsFrame/shootFrame
 * according to the PlayerState flags (shouldBreathe/shouldRun/shouldShoot).
 *
 * @return Indexes {torso_max, legs_max} for external use (compat).
 */
Indexes animate_clark(GRAPH* g, ScenarioState* sco_state, PlayerState* pla_state, AnimationArrays* ani_arrays);

#endif