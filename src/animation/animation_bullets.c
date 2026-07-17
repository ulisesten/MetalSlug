#include "animation_bullets.h"
#include "animation_player_clark.h"
#include "../constants/bullets.h"

void bulletDefaultArr(SDL_Rect frames[1]) {
    /* Default bullet sprite sub-region inside Weapon_SFX.png */
    frames[0].x = 5;
    frames[0].y = 72;
    frames[0].w = 6;
    frames[0].h = 6;
}

void initBulletAnimations(AnimationBulletArrays* ani_arrays) {
    bulletDefaultArr(ani_arrays->DefaultBullet);
}

void getBulletSrcRect(int type, const AnimationBulletArrays* a,
                      int frame, SDL_Rect* out_src) {
    switch (type) {
        case BULLET_DEFAULT: {
            const int count = (int)(sizeof(a->DefaultBullet) / sizeof(a->DefaultBullet[0]));
            int idx = frame;
            if (idx < 0)     idx = 0;
            if (idx >= count) idx = count - 1;
            *out_src = a->DefaultBullet[idx];
            break;
        }
        default:
            out_src->x = 0; out_src->y = 0;
            out_src->w = 0; out_src->h = 0;
            break;
    }
}

void initBulletPool(BulletPool* pool, SDL_Texture* bullet_texture) {
    for (int i = 0; i < BULLET_POOL_CAPACITY; i++) {
        pool->bullets[i].active        = false;
        pool->bullets[i].type          = BULLET_DEFAULT;
        pool->bullets[i].x             = 0;
        pool->bullets[i].y             = 0;
        pool->bullets[i].dx            = 0;
        pool->bullets[i].dy            = 0;
        pool->bullets[i].frame         = 0;
        pool->bullets[i].start_x       = 0;
        pool->bullets[i].lastAdvanceMs = 0;
    }
    pool->count   = 0;
    pool->texture = bullet_texture;
    pool->anim    = NULL;
}

/* Find first inactive slot and activate it. direction = DIRECTION_RIGHT (+1)
 * or DIRECTION_LEFT (-1). (x,y) is stored as the bullet's absolute world
 * position; the bullet then ignores any subsequent player movement. */
void spawnBullet(BulletPool* pool, int x, int y, int direction) {
    for (int i = 0; i < BULLET_POOL_CAPACITY; i++) {
        BulletState* b = &pool->bullets[i];
        if (!b->active) {
            b->active        = true;
            b->type          = BULLET_DEFAULT;
            b->x             = x;
            b->y             = y;          /* ABSOLUTE — not tracked to player */
            b->dx            = BULLET_SPEED_X * (direction == DIRECTION_LEFT ? -1 : 1);
            b->dy            = 0;
            b->frame         = 0;
            b->start_x       = x;
            b->lastAdvanceMs = SDL_GetTicks();
            return;
        }
    }
    /* No free slot — silently drop (pool full) */
}
