#pragma once
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <SDL3/SDL.h>
#include "constants.h"
#include "polygon.h"

typedef struct entity{
    bool exist;
    vect position;
    vect velocity;
    float angle;
    float angular_velocity;
    polygon* polygons[MAX_ENTITY_POLYGONS];
    int polygon_count;
    //float bounding_radius;
} entity;

entity entities[MAX_ENTITIES];
unsigned int entity_count = 0;

entity* new_entity(vect new_position, vect new_velocity, float new_angle, float new_angular_velocity, polygon** new_polygons, int new_polygon_count){
    if (entity_count == 100){
        printf("Max entities reached!\n");
        game_is_running = false;
        return NULL;
    }

    entity* new_entity = &entities[entity_count];
    new_entity->exist = true;
    new_entity->position = new_position;
    new_entity->velocity = new_velocity;
    new_entity->angle = new_angle;
    new_entity->angular_velocity = new_angular_velocity;
    new_entity->polygon_count = new_polygon_count;
    

    for (int poly=0; poly<new_polygon_count; poly++)
       new_entity->polygons[poly] = new_polygons[poly];

    entity_count++;
    return new_entity;
}

void new_meteor(vect new_position, vect new_velocity, float new_angle, float new_angluar_velocity){
    polygon* new_polygons[2];
    
    vect pentagon[5];
    vect hexagon[6];
    populate_points(pentagon, 5, 100);
    populate_points(hexagon, 6, 50);

    new_polygons[0] = new_polygon(true, pentagon, 5, set_vect(0, 0), 0);

    new_polygons[1] = new_polygon(true, hexagon, 6, set_vect(0, 0), 0);

    new_entity(new_position, new_velocity, new_angle, new_angluar_velocity, new_polygons, 2);
}

void update_entities(float delta_time){
    entity* current_entity = NULL;

    for (int e=0; e<MAX_ENTITIES; e++){
        current_entity = &entities[e];

        current_entity->position = add_vect(
            current_entity->position, 
            scale_vect(
                current_entity->velocity, 
                delta_time
            )
        );
        current_entity->angle += current_entity->angular_velocity * delta_time;
    }
}

