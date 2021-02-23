#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

int main(){

    if (SDL_Init( SDL_INIT_VIDEO | SDL_INIT_VIDEO ) > -1){
    
        std::cout << "SDL_Init Success" << std::endl;

    } else {

        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;

    }

    SDL_Quit();
    return 0;

}