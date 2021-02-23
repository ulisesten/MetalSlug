#ifndef SELECTION_MENU_H
#define SELECTION_MENU_H

#include <SDL2/SDL.h>

void menuPersonaje(    SDL_Surface* screen,SDL_Window*  window);//SelecciÃ³n de personaje
void elementosMenu(    SDL_Surface* screen,SDL_Surface* image);
void animEscotilla(    SDL_Surface* screen,SDL_Surface* image);
void select(           SDL_Surface* screen,SDL_Surface* image,int copia,int coor);

#endif