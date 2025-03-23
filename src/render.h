#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <SDL3/SDL.h>
#include "constants.h"
#include "player.h"
#include "camera.h"

SDL_Renderer* renderer = NULL;

void transform_entity_polygon();
void draw_polygon();
void draw_grid();

void render(){
    entity* current_entity = NULL;
    polygon* current_polygon = NULL;
    vect transformed_polygon[MAX_POLYGON_POINTS];

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    draw_grid();

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    for (int e=0; e<entity_count; e++){
        current_entity = &entities[e];

        if(current_entity->exist){
            for (int poly=0; poly<current_entity->polygon_count; poly++){
                current_polygon = current_entity->polygons[poly];
                transform_entity_polygon(transformed_polygon, current_entity, current_polygon);
                draw_polygon(transformed_polygon, current_polygon->point_count);
            }
        }
    }

    SDL_RenderPresent(renderer);
}

void transform_entity_polygon(vect* transformed_polygon, entity* current_entity, polygon* current_polygon){
    vect* current_point = NULL;
    vect* transformed_point = NULL;

    for(int h=0; h<current_polygon->point_count; h++){
        current_point = &current_polygon->points[h];

        // transform points to world coordinates
        transformed_polygon[h] = add_vect(
            rotate_vect(*current_point, current_polygon->angle + current_entity->angle), 
            add_vect(current_polygon->position, current_entity->position)
        );

        // displace relative to camera's position
        transformed_polygon[h] = add_vect(
            transformed_polygon[h], 
            scale_vect(camera.position, -1)
        );      

        // rotate relative to camera's angle
        transformed_polygon[h] = rotate_vect(
            transformed_polygon[h], 
            camera.angle * -1
        );
        
        // offset to make camera centered on window
        transformed_polygon[h] = add_vect(
            transformed_polygon[h], 
            set_vect(WINDOW_WIDTH/2, WINDOW_HEIGHT/2)
        );
    }
}

void draw_polygon(vect* transformed_polygon, int point_count){
    SDL_RenderLines(
        renderer, 
        transformed_polygon,
        point_count
    );
    SDL_RenderLine(
        renderer, 
        transformed_polygon[point_count - 1].x,
        transformed_polygon[point_count - 1].y,
        transformed_polygon[0].x,
        transformed_polygon[0].y
    );
}

void draw_grid(){
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    vect grid_line[2];

    for (int p=0; p<polygon_count; p++){
        if (!polygons[p].belongs_to_entity){

            for (int g=0; g<2; g++){
                grid_line[g] = add_vect(
                    polygons[p].points[g], 
                    polygons[p].position
                );

                grid_line[g] = add_vect(
                    grid_line[g], 
                    scale_vect(
                        mod_vect(camera.position, GRID_WIDTH), 
                        -1
                    )
                );

                grid_line[g] = rotate_vect(
                    grid_line[g], 
                    camera.angle * -1
                );

                grid_line[g] = add_vect(
                    grid_line[g], 
                    set_vect(WINDOW_WIDTH/2, WINDOW_HEIGHT/2)
                );
            }

            SDL_RenderLine(
                renderer, 
                grid_line[0].x, 
                grid_line[0].y, 
                grid_line[1].x, 
                grid_line[1].y
            );
        }
    }
}