#ifndef __ANIMATION_ENEMIES__
#define __ANIMATION_ENEMIES__

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "animation.h"


/// @brief EnemyModes
enum {
    MODE_CASUAL_1   = 1,
    MODE_SCARED     = 2,
    MODE_ATTACK
};

#define ENEMY_CONTACT 200

typedef struct {
    SDL_Rect enemyKnifeBody[18];
    SDL_Rect enemyScaredBody[11];
    SDL_Rect enemyCasualBody[12];
} AnimationEnemyArrays;

typedef struct {
    short BODY_MAX;
} EnemyIndexes;

typedef struct {
    short id;
    int x;
    int y;
    int h;
    int iBody;
    bool animate;
    short y_offset;
    short mode;
    short direction;
    Uint32 pastAnimate;
    AnimationEnemyArrays* ani_arrays;
    EnemyIndexes indexes;
} EnemyState;

void initEnemyAnimations(AnimationEnemyArrays* ene_arrays);
void initSoldierAnimations(AnimationEnemyArrays* ene_arrays);

void soldierKnifeArray(SDL_Rect body[18]);
void soldierScaredArray(SDL_Rect body[11]);
void soldierCasualArray(SDL_Rect body[12]);

EnemyIndexes soldierKnifeAttack(GRAPH g, EnemyState ene_state);
EnemyIndexes soldierScared(GRAPH g, EnemyState ene_state);
EnemyIndexes soldierCasual(GRAPH g, EnemyState ene_state);

#endif //__ANIMATION_ENEMIES__