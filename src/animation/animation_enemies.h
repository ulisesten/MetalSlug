#ifndef __ANIMATION_ENEMIES__
#define __ANIMATION_ENEMIES__

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "animation.h"


/// @brief EnemyModes
enum {
    MODE_CASUAL_1   = 1,
    MODE_SCARED     = 2,
    MODE_PURSUIT,
    MODE_ATTACK
};

#define ENEMY_CLOSE 300
#define ENEMY_CONTACT 45

typedef struct {
    SDL_Rect enemyKnifeBody[18];
    SDL_Rect enemyScaredBody[11];
    SDL_Rect enemyCasualBody[12];
    SDL_Rect enemyPursuitBody[12];
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
    Uint32 pastAnimate;
    bool walk;
    Uint32 pastWalk;
    bool isOperating;
    short y_offset;
    short mode;
    short direction;
    bool free_animation;
    AnimationEnemyArrays* ani_arrays;
    EnemyIndexes indexes;
    SDL_Texture* ene_texture;
} EnemyState;

void initEnemyAnimations(AnimationEnemyArrays* ene_arrays);
void initSoldierAnimations(AnimationEnemyArrays* ene_arrays);

void soldierKnifeArray(     SDL_Rect body[18]   );
void soldierScaredArray(    SDL_Rect body[11]   );
void soldierCasualArray(    SDL_Rect body[12]   );
void soldierPursuitArray(   SDL_Rect body[12]   );

EnemyIndexes soldierKnifeAttack(    GRAPH* g, EnemyState ene_state, int direction);
EnemyIndexes soldierScared(         GRAPH* g, EnemyState ene_state, int direction);
EnemyIndexes soldierCasual(         GRAPH* g, EnemyState ene_state, int direction);
EnemyIndexes soldierPursuit(        GRAPH* g, EnemyState ene_state, int direction);

#endif //__ANIMATION_ENEMIES__