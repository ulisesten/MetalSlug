#ifndef ANIMATION_H
#define ANIMATION_H

/**
 *Ulises Marínez Elías
 *06 de agosto de 2017
 *Funciones de manejo de sprites
*/

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef struct{
    SDL_Window* window;
    SDL_Surface* screen;
    SDL_Surface* player;
    SDL_Surface* playerBack;
}GRAPH;
//Escenarios
typedef struct{
    SDL_Window* window;
    SDL_Surface* screen;
    SDL_Surface* scene;
    int x;
    int xMountain;
    int xHorizon;
}SCENE;

/**Arrays Medidas de blitsruface para sprites*/
void clarkStandSetRect(             SDL_Rect torzo[4],SDL_Rect pierna[4]);
void clarkLowerBodyRunSetRect(      SDL_Rect lowerBody[6]);
void clarkUpperBodyShootSetRect(    SDL_Rect upperBody[9]);//Sprites de disparo

void clarkStandBackArr(             SDL_Rect torzo[4],SDL_Rect pierna[4]);
void clarkRunArr(                   SDL_Rect torzo[4],SDL_Rect pierna[4]);
void clarkRunBackArr(               SDL_Rect torzo[4],SDL_Rect pierna[4]);
void clarkJump(                     int piso[]);//Coordenadas de salto

/**Funciones Movimiento*/
void clarkStand(GRAPH g,int *iT,int *iP,int x,int y,SDL_Rect torzo[],SDL_Rect pierna[]);
void clarkRun(GRAPH g,int iT,int iP,int x,int y,SDL_Rect torzo[],SDL_Rect pierna[]);
void clarkStandBack(GRAPH g,int iT,int iP,int x,int y,SDL_Rect torzo[],SDL_Rect pierna[]);
void clarkRunBack(GRAPH g,int iT,int iP,int x,int y,SDL_Rect torzo[],SDL_Rect pierna[]);
void clarkShoot(GRAPH g,int *iT,int x,int y,SDL_Rect torzo[]);
void clarkPier(GRAPH g,int x,int y,SDL_Rect pierna[]);

#endif