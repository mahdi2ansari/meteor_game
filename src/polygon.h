#include <stdio.h>
#include <stdbool.h>
#include <SDL3/SDL.h>
#include "constants.h"
#include "vector.h"

typedef struct polygon{
    bool exist;
    bool belongs_to_entity;
    vect points[MAX_POLYGON_POINTS];
    int point_count;
    vect position;
    float angle;
} polygon;

polygon polygons[MAX_POLYGONS];
unsigned int polygon_count = 0;

polygon* new_polygon(bool belongs_to_entity, vect* new_points, int new_point_count, vect new_position, float new_angle){
    if (polygon_count == MAX_POLYGONS){
        printf("Max polygons reached!\n");
        game_is_running = false;
        return NULL;
    }

    polygon* new_polygon = &polygons[polygon_count];
    new_polygon->exist = true;
    new_polygon->belongs_to_entity = belongs_to_entity;
    new_polygon->point_count = new_point_count;
    new_polygon->position = new_position;
    new_polygon->angle = new_angle;
    for (int i=0; i<new_point_count; i++)
        new_polygon->points[i] = new_points[i];

    polygon_count++;
    return new_polygon;
}

bool populate_points(vect* new_points, int new_shape_point_count, float radius){
    if (new_shape_point_count < 2 || new_shape_point_count > MAX_POLYGON_POINTS){
        printf("polygon creation failed, invalid amount of points!\n");
        game_is_running = false;
        return false;
    }

    float theta = 2*PI/new_shape_point_count;
    for (int p=0; p<new_shape_point_count; p++){
        (new_points + p)->x = radius*cos(theta*p);
        (new_points + p)->y = radius*sin(theta*p);
    }

    return true;
}

void create_grid(int grid_width){
    vect vertical[2] = {set_vect(0, 0), set_vect(0, 2*WINDOW_HEIGHT)};
    vect horizontal[2] = {set_vect(0, 0), set_vect(2*WINDOW_WIDTH, 0)};

    int vertical_count = WINDOW_WIDTH / grid_width;
    int horizontal_count = WINDOW_HEIGHT / grid_width;

    for (int x=-vertical_count; x<vertical_count; x++)
        new_polygon(false, vertical, 2, set_vect(x*grid_width, -WINDOW_HEIGHT), 0);

    for (int y=-horizontal_count; y<horizontal_count; y++)
        new_polygon(false, horizontal, 2, set_vect(-WINDOW_WIDTH, y*grid_width), 0);
}