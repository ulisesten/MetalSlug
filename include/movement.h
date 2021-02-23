#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <SDL2/SDL.h>

typedef struct {

    SDL_Rect floorRect;
    SDL_Rect traceRect;
    SDL_Rect horizonRect;
    SDL_Rect skyRect;
    SDL_Rect playerSpriteFrame;
    SDL_Rect playerUpperBodyPosition;
    SDL_Rect playerLowerBodyPosition;
    SDL_Rect playerLowerBodyPositionBackward;

    int fullScreenHightCompensation = 0;

} Rects;

typedef struct {
    SDL_Event e;
    bool key_left     =     false;
    bool key_right    =     false;
    bool key_down     =     false;
    bool key_up       =     false;
    bool key_shoot    =     false;
    bool key_jump     =     false;
} Events;

typedef struct {
    bool isShooting = false;
} Actions;

typedef struct {
    int upperBodyStandIndex = 0;
    int upperBodyShootIndex = 0;
    int lowerBodyStandIndex = 0;
    int lowerBodyRunIndex   = 0;
} Indices;

void handleEvents(Rects* rects, SDL_Window* window, Events* events, Indices* i, int hight);
void ToggleFullscreen(SDL_Window* Window);

#endif