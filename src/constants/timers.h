#ifndef CONSTANTS_TIMERS_H
#define CONSTANTS_TIMERS_H

/* Player animation timers (ms) */
#define BREATH_INTERVAL_MS          200
#define WALK_INTERVAL_MS             94
#define SHOOT_INTERVAL_MS            20
#define TRANSLATE_INTERVAL_MS         9

/* Jump timers (independent — sprite cycle vs. parabolic trajectory) */
#define JUMP_ANIM_INTERVAL_MS        170 /* sprite frame cycling while jumping */
#define JUMP_TRAJECTORY_INTERVAL_MS  20 /* parabolic height advance */

/* Death animation timer (ms per frame advance of clarkDeadByShoot strip) */
#define DEATH_ANIM_INTERVAL_MS       110

/* Enemy death-by-bullet animation timers (ms) */
#define ENEMY_DEAD_ANIM_INTERVAL_MS  90
#define ENEMY_BLINK_INTERVAL_MS      120

/* Enemy animation timers (ms) */
#define ENEMY_ANIMATE_INTERVAL_MS 90
#define ENEMY_WALK_INTERVAL_MS    20

#endif
