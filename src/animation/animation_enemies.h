#ifndef __ANIMATION_ENEMIES__
#define __ANIMATION_ENEMIES__

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "animation_player_clark.h"


typedef struct {
    short type;
    short mode;
    int x;
    int y;
} EnemyMatrixData;

typedef struct {
    EnemyMatrixData* matrix;
    short count;
} EnemyMatrix;


/// @brief EnemyModes
enum {
    MODE_CASUAL_1   = 1,
    MODE_SCARED     = 2,
    MODE_PURSUIT,
    MODE_ATTACK
};

/// @brief EnemyTypes
enum {
    BASIC_SOLDIER = 1,
};

#include "../constants/enemies.h"

typedef struct {
    SDL_Rect enemyKnifeBody[18];
    SDL_Rect enemyScaredBody[11];
    SDL_Rect enemyCasualBody[12];
    SDL_Rect enemyPursuitBody[12];
    SDL_Rect enemyDeadByShootBody[9]; /* death animation when hit by bullet */
} AnimationEnemyArrays;

typedef struct {
    short maxBodyFrames;
} EnemyIndexes;

typedef struct {
    short id;
    int x;
    int y;
    int floorIndex;
    int bodyFrame;
    bool shouldAnimate;
    Uint32 lastAnimateTick;
    bool shouldWalk;
    Uint32 lastWalkTick;
    bool hasReacted;
    short spriteVerticalOffset;
    int scenarioScrollOffset;
    short type;
    short mode;
    short direction;
    bool canTransitionMode;
    bool isDead;                 /* killed (e.g. stomped by a jumping player) */
    bool isDying;                /* playing death-by-bullet animation */
    bool isBlinking;             /* post-death blink before removal */
    bool shouldRemove;           /* blink finished; mark for cleanup */
    int deadFrame;               /* 0..ENEMY_DEAD_FRAMES-1 during isDying */
    int blinkFrame;              /* 0..ENEMY_BLINK_FRAMES-1 during isBlinking */
    Uint32 lastDeadTick;         /* timer for deadFrame advance */
    Uint32 lastBlinkTick;        /* timer for blink toggle */
    AnimationEnemyArrays* animations;
    EnemyIndexes indexes;
    SDL_Texture* texture;
    SDL_Rect lastBodyDstRect;   /* debug — last drawn destination rect */
} EnemyState;

void initEnemyAnimations(AnimationEnemyArrays* ene_arrays);
void initSoldierAnimations(AnimationEnemyArrays* ene_arrays);

void soldierKnifeArray(     SDL_Rect body[18]   );
void soldierScaredArray(    SDL_Rect body[11]   );
void soldierCasualArray(    SDL_Rect body[12]   );
void soldierPursuitArray(   SDL_Rect body[12]   );
void soldierDeadByShootArray(SDL_Rect body[9]   );

/* Render functions. They take an optional SDL_Rect* dst_cache for debug
 * collision visualisation. */
EnemyIndexes soldierKnifeAttack(    GRAPH* g, EnemyState ene_state, int direction, SDL_Rect* dst_cache);
EnemyIndexes soldierScared(         GRAPH* g, EnemyState ene_state, int direction, SDL_Rect* dst_cache);
EnemyIndexes soldierCasual(         GRAPH* g, EnemyState ene_state, int direction, SDL_Rect* dst_cache);
EnemyIndexes soldierPursuit(        GRAPH* g, EnemyState ene_state, int direction, SDL_Rect* dst_cache);
EnemyIndexes soldierDeadByShoot(    GRAPH* g, EnemyState ene_state, int direction, SDL_Rect* dst_cache);

#endif //__ANIMATION_ENEMIES__