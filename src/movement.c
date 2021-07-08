#include "movement.h"

void handleEvents(SDL_Window* window, Events* events, Indices* i, int hight){

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
                events->fullscreen = !events->fullscreen;
                //printf("fullscreen %d\n", events->fullscreen); 
            }

            else if(events->e.key.keysym.sym == SDLK_ESCAPE){//Derecha
                SDL_SetWindowFullscreen(window, false);
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

}

void ToggleFullscreen(SDL_Window* window) {

    Uint32 FullscreenFlag = SDL_WINDOW_FULLSCREEN;

    bool IsFullscreen = SDL_GetWindowFlags(window) & FullscreenFlag;
    SDL_SetWindowFullscreen(window, IsFullscreen ? 0 : FullscreenFlag);
    SDL_ShowCursor(IsFullscreen);

}
