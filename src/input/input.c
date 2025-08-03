// input.c
#include "input.h"
#include <SDL2/SDL.h>
#include <stdlib.h>

extern void exitGame(PlayerState* state);  // puedes implementar esto si quieres terminar el juego desde fuera

void handleEvents(PlayerState* state) {
    SDL_Event e;
    SDL_PollEvent(&e);
    //while (SDL_PollEvent(&e)) {
        switch (e.type) {
            case SDL_QUIT:
                state->quit = true;
                break;

            case SDL_KEYDOWN:
                switch (e.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        state->quit = true;
                        break;
                    case SDLK_RIGHT:
                        state->IS_RUNNING_FORWARD= true;
                        state->direction = DIRECTION_RIGHT;
                        state->directionAux = DIRECTION_RIGHT;
                        break;
                    case SDLK_LEFT:
                        state->IS_RUNNING_BACKWARD = true;
                        state->direction = DIRECTION_LEFT;
                        state->directionAux = DIRECTION_LEFT;
                        break;
                    case SDLK_s:
                        state->jump = true;
                        break;
                    case SDLK_x:
                        //state->key_shoot = true;
                        state->isShooting = true;
                        break;
                    case SDLK_f:
                        state->fullscreen = true;
                        break;
                }
                break;

            case SDL_KEYUP:
                switch (e.key.keysym.sym) {
                    case SDLK_RIGHT:
                        state->IS_RUNNING_FORWARD = false;
                        break;
                    case SDLK_LEFT:
                        state->IS_RUNNING_BACKWARD = false;
                        break;
                    case SDLK_x:
                        //state->key_shoot = false;
                        state->isShooting = false;
                        break;
                }
                if (!state->jump) {
                    state->directionAux = 0;
                }
                break;

            case SDL_JOYBUTTONDOWN:
                if (e.jbutton.button == 2) {
                    state->jump = true;
                }
                if (e.jbutton.button == 5) {
                    state->key_shoot = true;
                    state->isShooting = 3;
                }
                break;

            case SDL_JOYAXISMOTION:
                if (e.jaxis.axis == 0) {
                    if (e.jaxis.value == 0) {
                        state->IS_RUNNING_FORWARD = false;
                        state->IS_RUNNING_BACKWARD = false;
                        if (!state->jump)
                            state->directionAux = 0;
                    } else if (e.jaxis.value > 0) {
                        state->IS_RUNNING_FORWARD = true;
                        state->direction = DIRECTION_RIGHT;
                        state->directionAux = DIRECTION_RIGHT;
                        state->keepWalking = true;
                    } else if (e.jaxis.value < 0) {
                        state->IS_RUNNING_BACKWARD = true;
                        state->direction = DIRECTION_LEFT;
                        state->directionAux = DIRECTION_LEFT;
                        state->keepWalking = true;
                    }
                }
                break;
        }
    //}
}