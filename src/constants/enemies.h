#ifndef CONSTANTS_ENEMIES_H
#define CONSTANTS_ENEMIES_H

/* Enemy proximity distances (in floor-index units) */
#define ENEMY_CLOSE_DISTANCE   300
#define ENEMY_CONTACT_DISTANCE 45

/* Enemy sprite placement offsets (px) */
#define ENEMY_SPAWN_X_OFFSET    25 /* subtracted from matrix x at spawn */
#define ENEMY_VERTICAL_OFFSET   24 /* added to terrain height */

/* Death-by-bullet animation */
#define ENEMY_DEAD_FRAMES       9
#define ENEMY_BLINK_FRAMES      6  /* number of blink on/off toggles */

#endif
