#pragma once
#include <stdio.h>
#include <stdbool.h>
#include <SDL3/SDL.h>
#include "constants.h"
#include "entity.h"

typedef struct PLAYER{
    entity* entity;
    bool up, down, left, right;
} PLAYER;

PLAYER player;

void add_player(){
    polygon* player_polygons[1];
    vect triangle[3];
    populate_points(triangle, 3, 50);

    player_polygons[0] = new_polygon(
        true, 
        triangle, 
        3, 
        set_vect(0, 0), 
        -PI/2
    );

    player.entity = new_entity(
        set_vect(0, 0), 
        set_vect(0, 0), 
        0, 
        0, 
        player_polygons, 
        1
    );
}

void update_player(){
    player.entity->velocity = set_vect(0, 0);
    player.entity->angular_velocity = 0;

    if (player.up){
        player.entity->velocity = rotate_vect(
            set_vect(0, -200), 
            player.entity->angle
        );
    }

    if (player.right)
        player.entity->angular_velocity = 2;
    if (player.left)
        player.entity->angular_velocity = -2;

    player.up = false;
    player.down = false;
    player.right = false;
    player.left = false;
}
