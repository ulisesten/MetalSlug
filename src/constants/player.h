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

/* Vertical offset (px) added to player.y when drawing the torso sprite,
 * relative to the standing pose. Used as the base for the jump correction
 * below. */
#define PLAYER_TORSO_Y_OFFSET 20

/* Vertical offset (px) added to player.y when drawing the legs sprite. */
#define PLAYER_LEGS_Y_OFFSET 41

/* Extra px added to the torso Y while jumping, to correct the desync
 * between the jump torso sprite and the legs sprite. */
#define PLAYER_JUMP_TORSO_Y_OFFSET 1

/* Extra horizontal correction (px) applied to the torso X when the player
 * is simultaneously jumping AND shooting while facing left. The combined
 * pose uses a different sprite whose left-facing variant is shifted
 * relative to the regular jump torso, so we nudge the draw position. */
#define PLAYER_JUMP_TORSO_X_OFFSET 3
#define PLAYER_JUMP_TORSO_LEFT_X_OFFSET 5

#define PLAYER_JUMB_SHOOTING_TORSO_X_OFFSET 4
#define PLAYER_JUMB_SHOOTING_TORSO_LEFT_X_OFFSET 10

#endif
