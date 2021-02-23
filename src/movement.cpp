#include "movement.h"

void handleEvents(Rects* rects, SDL_Window* window, Events* events, Indices* i, int hight){

    if (SDL_PollEvent(&events->e)) {
        /**Handle press and release keys */
        if(events->e.type == SDL_KEYDOWN) { 
            if(events->e.key.keysym.sym == SDLK_RIGHT){
                events->key_right = true;      
            }

            else if(events->e.key.keysym.sym == SDLK_LEFT){
                events->key_left = true;
            }
            
            else if(events->e.key.keysym.sym == SDLK_f){//Derecha
                ToggleFullscreen(window);     
            }

            else if(events->e.key.keysym.sym == SDLK_ESCAPE){//Derecha
                SDL_SetWindowFullscreen(window, false);
                //exit(0);
            }

            if(events->e.key.keysym.sym == SDLK_s){
                        events->key_jump = true;
            }

            if( events->e.key.keysym.sym == SDLK_x ){
                if(!events->key_shoot)
                    i->upperBodyShootIndex = 3;
                else
                    i->upperBodyShootIndex = 0;
                events->key_shoot = true;
            }
		}

        if(events->e.type == SDL_KEYUP) {

            if(events->e.key.keysym.sym == SDLK_RIGHT){//Derecha
                events->key_right = false;
            }

            else if(events->e.key.keysym.sym == SDLK_LEFT){
                events->key_left = false;
            }

        }

        if (events->e.type == SDL_QUIT) {
            exit(0);
        }
    }

    if(SDL_GetWindowFlags(window) & SDL_WINDOW_FULLSCREEN)
        hight += rects->fullScreenHightCompensation;

    rects->playerUpperBodyPosition.y = hight;
    rects->playerLowerBodyPosition.y = 21 + hight;
    rects->playerLowerBodyPositionBackward.y = 21 + hight;

    /**Movement */
    if(events->key_right) {
        rects->playerUpperBodyPosition.x+=1;
        rects->playerLowerBodyPosition.x+=1;
        rects->playerLowerBodyPositionBackward.x+=1;
    }

    else if(events->key_left) {
        rects->playerUpperBodyPosition.x-=1;
        rects->playerLowerBodyPosition.x-=1;
        rects->playerLowerBodyPositionBackward.x-=1;
    }

}

void ToggleFullscreen(SDL_Window* window) {

    Uint32 FullscreenFlag = SDL_WINDOW_FULLSCREEN;

    bool IsFullscreen = SDL_GetWindowFlags(window) & FullscreenFlag;
    SDL_SetWindowFullscreen(window, IsFullscreen ? 0 : FullscreenFlag);
    SDL_ShowCursor(IsFullscreen);

}
