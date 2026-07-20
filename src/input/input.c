// input.c
#include "input.h"
#include "constants/player.h"
#include <SDL2/SDL.h>
#include <stdlib.h>

extern void exitGame(PlayerState* state);  // puedes implementar esto si quieres terminar el juego desde fuera

void handleEvents(PlayerState* state) {
    SDL_Event e;
    /* Drain the whole event queue each frame. Processing only one event per
     * frame (the old behaviour) lets the queue back up under bursty input —
     * e.g. holding a key generates SDL_KEYDOWN auto-repeat events faster than
     * the framerate processes them, and a quick KEYUP+KEYDOWN pair can be
     * split across frames, producing visible input lag. The switches below
     * are all idempotent on the state they write, so re-entering them with
     * multiple events of the same type is harmless. */
    while (SDL_PollEvent(&e)) {
        /* Ignore gameplay inputs once dead, but keep ESC/QUIT working. */
        const bool dead = state->shouldDie || state->isDead;
        switch (e.type) {
            case SDL_QUIT:
                state->quit = true;
                break;

            case SDL_KEYDOWN:
                if (dead && e.key.keysym.sym != SDLK_ESCAPE) break;
                switch (e.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        state->quit = true;
                        break;
                    case SDLK_RIGHT:
                        state->isMovingForward= true;
                        state->direction = DIRECTION_RIGHT;
                        state->lastDirection = DIRECTION_RIGHT;
                        break;
                    case SDLK_LEFT:
                        state->isMovingBackward = true;
                        state->direction = DIRECTION_LEFT;
                        state->lastDirection = DIRECTION_LEFT;
                        break;
                    case SDLK_UP:
                        state->shouldLookUp = true;
                        break;
                    case SDLK_s:
                        if (e.key.repeat == 0) {
                            /* Edge-triggered manual shot — only fires once per
                             * physical key press, never on auto-repeat. */
                            state->pendingShot = true;
                        }
                        state->wantToShoot = true;
                        if (state->shotsRemaining > 0) {
                            state->shootFrame    = SHOOT_RESTART_FRAME;
                            state->lastShootTick = SDL_GetTicks();
                        } else {
                            state->shotsRemaining = PLAYER_SHOT_FRAMES;
                        }
                        break;
                    case SDLK_SPACE:
                        state->shouldJump = true;
                        break;
                    case SDLK_f:
                        if (e.key.repeat == 0) {
                            state->fullscreen = true;
                        }
                        break;
                    case SDLK_y:  /* the `~ key — common debug toggle */
                        if (e.key.repeat == 0) {
                            state->showDebugRects = !state->showDebugRects;
                            printf("[DEBUG] showDebugRects = %s\n", state->showDebugRects ? "ON" : "OFF");
                        }
                        break;
                }
                break;

            case SDL_KEYUP:
                switch (e.key.keysym.sym) {
                    case SDLK_RIGHT:
                        state->isMovingForward = false;
                        break;
                    case SDLK_LEFT:
                        state->isMovingBackward = false;
                        break;
                    case SDLK_UP:
                        state->shouldLookUp = false;
                        break;
                }
                if (!state->shouldJump) {
                    state->lastDirection = 0;
                }
                break;

            case SDL_JOYBUTTONDOWN:
                if (e.jbutton.button == 2) {
                    state->shouldJump = true;
                }
                if (e.jbutton.button == 5) {
                    state->pendingShot = true;
                    state->wantToShoot = true;
                    if (state->shotsRemaining > 0) {
                        state->shootFrame    = SHOOT_RESTART_FRAME;
                        state->lastShootTick = SDL_GetTicks();
                    } else {
                        state->shotsRemaining = PLAYER_SHOT_FRAMES;
                    }
                }
                break;

            case SDL_JOYAXISMOTION:
                if (e.jaxis.axis == 0) {
                    if (e.jaxis.value == 0) {
                        state->isMovingForward = false;
                        state->isMovingBackward = false;
                        if (!state->shouldJump)
                            state->lastDirection = 0;
                    } else if (e.jaxis.value > 0) {
                        state->isMovingForward = true;
                        state->direction = DIRECTION_RIGHT;
                        state->lastDirection = DIRECTION_RIGHT;
                        state->keepWalking = true;
                    } else if (e.jaxis.value < 0) {
                        state->isMovingBackward = true;
                        state->direction = DIRECTION_LEFT;
                        state->lastDirection = DIRECTION_LEFT;
                        state->keepWalking = true;
                    }
                }
                break;
        }
    }
}
