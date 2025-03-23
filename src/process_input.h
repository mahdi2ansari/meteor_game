#include <stdio.h>
#include <SDL3/SDL.h>
#include "constants.h"
#include "player.h"

void process_input(){
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type){
        case SDL_EVENT_QUIT:
            printf("Quitting Program\n");
            game_is_running = false;
            break;
        case SDL_EVENT_KEY_DOWN:
            if (event.key.key == SDLK_ESCAPE)
                game_is_running = false;
            break;
    }

    SDL_PumpEvents();
    if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_UP])
        player.up = true;
    if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_DOWN])
        player.down = true;
    if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_RIGHT])
        player.right = true;
    if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_LEFT])
        player.left = true;

}