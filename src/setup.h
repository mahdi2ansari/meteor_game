#include <stdio.h>
#include <SDL3/SDL.h>
#include "constants.h"
#include "player.h"

void setup(){
    create_grid(GRID_WIDTH);
    add_player();
    new_meteor(set_vect(250, -300), set_vect(-30, 15), 0, 2);
    new_meteor(set_vect(-350, 200), set_vect(50, -30), 0, -1);
}