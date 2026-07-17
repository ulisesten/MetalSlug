#ifndef CONSTANTS_BULLETS_H
#define CONSTANTS_BULLETS_H

/* Bullet pool sizing */
#define BULLET_POOL_CAPACITY 22

/* Bullet horizontal velocity in px/frame */
#define BULLET_SPEED_X 1

/* Spawn offset relative to player.x (approximate muzzle position) */
#define BULLET_SPAWN_OFFSET_X 36

/* Vertical position of bullet (matches player torso y ~ +20) */
#define BULLET_SPAWN_OFFSET_Y 26

/* Bullets are despawned after traveling this many pixels horizontally */
#define BULLET_TRAVEL_RANGE 800

/* Minimum time (ms) between two bullets when the player holds or
 * repeatedly taps S. Tune up for slower fire-rate, down for faster. */
#define BULLET_COOLDOWN_MS 80

/* How often (ms) each bullet advances its position. Motion is timer-driven
 * so it is FPS-independent. */
#define BULLET_ADVANCE_INTERVAL_MS 5  /* ≈ 60Hz tick */
#define BULLET_ADVANCE_STEP_X       3  /* px per advance tick */

#endif
