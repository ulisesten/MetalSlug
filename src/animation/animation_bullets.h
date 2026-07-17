#ifndef ANIMATION_BULLETS_H
#define ANIMATION_BULLETS_H

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "../constants/bullets.h"
#include "animation_player_clark.h"

/* Bullet types. Add more as the player picks up weapons. */
enum {
    BULLET_DEFAULT = 1,
};

/* Per-type sprite frame strips. Each entry holds every frame of its animation. */
typedef struct {
    SDL_Rect DefaultBullet[1];
} AnimationBulletArrays;

typedef struct {
    int  type;        /* BULLET_DEFAULT, etc. */
    int  x, y;        /* current world position (y is ABSOLUTE — set at spawn, never tracked to player) */
    int  dx, dy;      /* velocity (px per frame, but stepped via timer) */
    bool active;      /* live / should be rendered */
    int  frame;       /* current frame index inside the type's strip */
    int  start_x;     /* spawn x used to compute travel range */
    Uint32 lastAdvanceMs; /* timestamp of last advance tick */
} BulletState;

typedef struct {
    BulletState bullets[BULLET_POOL_CAPACITY];
    int count;
    SDL_Texture* texture;
    AnimationBulletArrays* anim;
} BulletPool;

/* Frame-array factory functions (only Default for now). */
void bulletDefaultArr(SDL_Rect frames[1]);

/* Top-level init: calls all *Arr factories. */
void initBulletAnimations(AnimationBulletArrays* ani_arrays);

/* Pick the right strip for the given bullet type and copy the current frame's
 * source rect into out_src. */
void getBulletSrcRect(int type, const AnimationBulletArrays* a,
                      int frame, SDL_Rect* out_src);

/* Pool helpers */
void initBulletPool(BulletPool* pool, SDL_Texture* bullet_texture);
void spawnBullet(BulletPool* pool, int x, int y, int direction);

#endif /* ANIMATION_BULLETS_H */
