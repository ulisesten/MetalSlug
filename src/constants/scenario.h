#ifndef CONSTANTS_SCENARIO_H
#define CONSTANTS_SCENARIO_H

/* Scenario total scroll width (px) */
#define SCENARIO_MAX_WIDTH 3320

/* Initial scenario viewport dimensions (px) */
#define SCENARIO_BASE_W 555
#define SCENARIO_BASE_Y 10

/* Scroll ratios: how many px of foreground scroll before background moves 1px */
#define MOUNTAIN_SCROLL_RATIO_VALUE  4
#define HORIZON_SCROLL_RATIO_VALUE 18

/* Offset applied when player reaches the end of the scenario */
#define SCENARIO_END_OFFSET_VALUE 80

/* Parallax layer source rectangles (px in spritesheet) */
#define SKY_SRC_X      10
#define SKY_SRC_W     560
#define SKY_SRC_H     112
#define HORIZON_DEST_W 555
#define HORIZON_DEST_H 180

#define MOUNTAIN_DEST_X  10
#define MOUNTAIN_SRC_W  502
#define MOUNTAIN_SRC_H  168
#define MOUNTAIN_DEST_Y 560
#define MOUNTAIN_COORS_Y 57
#define MOUNTAIN_COORS_H 180

#define GROUND_SRC_X     10
#define GROUND_COORS_X   0
#define GROUND_COORS_Y  10
#define GROUND_COORS_W 502
#define GROUND_COORS_H 240
#define GROUND_DEST_W  502
#define GROUND_DEST_H  250

#define GROUND_HEIGHT_OFFSET 23
#endif
