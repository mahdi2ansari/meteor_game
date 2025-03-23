#pragma once
#include <stdio.h>
#include <SDL3/SDL.h>
#include <math.h>
#include "constants.h"

typedef struct CAMERA{
    vect position;
    vect velocity;
    float angle;
    float angluar_velcocity;
    float zoom;
}CAMERA;

CAMERA camera;

void setup_camera(){
    camera.position = set_vect(0, 0);
    camera.velocity = set_vect(0, 0);
    camera.angle = 0;
    camera.angluar_velcocity = 0;
    camera.zoom = 0;
}

void update_camera(float delta_time){
    camera.velocity = set_vect(0, 0);
    camera.angluar_velcocity = 0;

    float dist_to_player = dist(camera.position, player.entity->position);

    if (dist_to_player > 1){
        camera.velocity = scale_vect(
            sub_vect(player.entity->position, camera.position), 
            pow(dist_to_player, 2)/2500
        );
    }

    camera.angluar_velcocity = player.entity->angular_velocity;

    camera.position = add_vect(
        camera.position,
        scale_vect(camera.velocity, delta_time)
    );

    camera.angle += camera.angluar_velcocity * delta_time;
}