#ifndef CONSTANTS_PLAYER_H
#define CONSTANTS_PLAYER_H

/* Player starting floor index in the terrain array */
#define PLAYER_START_FLOOR_INDEX 25

/* Player movement range on screen (px) */
#define PLAYER_X_RANGE_MIN 20
#define PLAYER_X_RANGE_MAX 400

/* Shooting burst count (each key press triggers N frames) */
#define PLAYER_SHOT_FRAMES 3

/* Frame index to restart the shoot animation at when the player
 * presses shoot again mid-burst (skips the initial muzzle flash). */
#define SHOOT_RESTART_FRAME 3

#endif
