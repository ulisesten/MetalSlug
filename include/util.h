#ifndef UTIL_H
#define UTIL_H

#include <SDL2/SDL.h>
#include <stdbool.h>

typedef struct{
    SDL_Window* window;
    SDL_Surface* screen;
    SDL_Surface* scene;
    int x;
    int xMountain;
    int xHorizon;
}SCENE;

typedef struct {
	SDL_Window*      window              ;
	SDL_Surface*     screen              ;
	SDL_Renderer*    sceneRenderer       ;
	SDL_Renderer*    playerRenderer      ;
	SDL_Texture*     sceneFloorTexture   ;
    SDL_Texture*     sceneHorizonTexture ;
    SDL_Texture*     sceneSkyTexture     ;
	SDL_Texture*     playerTexture       ;
    SDL_RendererFlip rendererFlip        ;
}Graphic_elements;


typedef struct {
    SDL_Rect floorRect;
    SDL_Rect traceRect;
    SDL_Rect horizonRect;
    SDL_Rect skyRect;
    SDL_Rect playerSpriteFrame;

    SDL_Rect upperBodyBaseRect;
    SDL_Rect upperBodyRect[4];
    SDL_Rect upperBodyShootRect[9];
    SDL_Rect lowerBodyBaseRect;
    SDL_Rect lowerBodyRect[4];
    SDL_Rect lowerBodyRunRect[6];


    SDL_Rect playerUpperBodyPosition;
    SDL_Rect playerLowerBodyPosition;
    SDL_Rect playerLowerBodyPositionBackward;
    int      fullScreenHightCompensation;
} Rects;

typedef struct {
    SDL_Event e;
    bool key_left  ;
    bool key_right ;
    bool key_down  ;
    bool key_up    ;
    bool key_shoot ;
    bool key_jump  ;
    bool fullscreen;
} Events;

//typedef struct {
//    bool isShooting;
//} Actions;

typedef struct {
    int upperBodyStandIndex;
    int upperBodyShootIndex;
    int lowerBodyStandIndex;
    int lowerBodyRunIndex  ;
} Indices;


struct SdlConfig {
    Graphic_elements graph_elements;
    Rects            rects;
    Indices          i;
};

void setRects(         Rects*           rects );
void settingFloorHight(int floor[]);
void readMeasurements( int array[], const char* file_name, int length);
void clarkStandSetRect(             SDL_Rect torzo[4],SDL_Rect pierna[4]);
void clarkLowerBodyRunSetRect(      SDL_Rect lowerBody[6]);
void clarkUpperBodyShootSetRect(    SDL_Rect upperBody[9]);//Sprites de disparo
void setConfiguration(struct SdlConfig* config);

#endif