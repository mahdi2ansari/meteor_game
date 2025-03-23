#include <stdio.h>
#include <stdbool.h>
#include <SDL3/SDL.h>
#include "constants.h"
#include "setup.h"
#include "process_input.h"
#include "update.h"
#include "render.h"

SDL_Window* window = NULL;

bool initialize_window();
void destroy_window();

int main(int argc, char* argv[]){
    printf("game.exe has run!\n");
    game_is_running = initialize_window();
    setup();
    setup_camera();

    while (game_is_running){
        process_input();
        update();
        render();
    }

    destroy_window();
    return 0;
}

bool initialize_window(){
    if (!SDL_Init(SDL_INIT_VIDEO)){
        fprintf(stderr, "SDL3 Initialization fail\n");
        return false;
    }

    window = SDL_CreateWindow(
        NULL,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_BORDERLESS
    );
    if (!window){
        fprintf(stderr, "SDL window creation error\n");
        return false;
    }

    renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer){
        fprintf(stderr, "SDL renderer creation error\n");
        return false;
    }

    return true;
}

void destroy_window(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}