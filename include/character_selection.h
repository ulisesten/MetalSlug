#ifndef CHARACTER_SELECTION_H
#define CHARACTER_SELECTION_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void character_selection(    SDL_Surface* screen,SDL_Window*  window);//SelecciÃ³n de personaje
void elementosMenu(    SDL_Surface* screen,SDL_Surface* image);
void animEscotilla(    SDL_Surface* screen,SDL_Surface* image);
void selection(           SDL_Surface* screen,SDL_Surface* image,int copia,int coor);

#endif