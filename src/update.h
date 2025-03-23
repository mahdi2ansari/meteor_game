#include <stdio.h>
#include <SDL3/SDL.h>
#include "constants.h"
#include "entity.h"
#include "camera.h"

int last_frame_time = 0;

void update(){
    int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - last_frame_time);
    if (time_to_wait > 0 && FPS_IS_CAPPED)
        SDL_Delay(time_to_wait);
        
    float delta_time = (SDL_GetTicks() - last_frame_time) / 1000.0f;

    update_player();
    update_camera(delta_time);
    update_entities(delta_time);

    last_frame_time = SDL_GetTicks();
}