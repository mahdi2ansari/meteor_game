#pragma once
#include <stdio.h>
#include <math.h>
#include <SDL3/SDL.h>
#include "constants.h"

typedef SDL_FPoint vect;

vect set_vect(float X, float Y){
    vect vect1;
    vect1.x = X;
    vect1.y = Y;
    return vect1;
}

vect add_vect(vect vect1, vect vect2){
    return set_vect(
        vect1.x + vect2.x, 
        vect1.y + vect2.y
    );
}

vect scale_vect(vect vect1, float scalar){
    return set_vect(
        vect1.x * scalar, 
        vect1.y * scalar
    );
}

// clockwise is positive, counterclockwise is negative
// this is due to the y-axis of the screen increasing downwards, as opposed to a normal cartesian grid where y increases upwards.
vect rotate_vect(vect vect1, float angle){
    return set_vect(
        vect1.x*cos(angle) - vect1.y*sin(angle), 
        vect1.x*sin(angle) + vect1.y*cos(angle)
    );
}

vect mod_vect(vect vect1, int mod){
    return set_vect(
        (int)vect1.x % mod, 
        (int)vect1.y % mod
    );
}

vect sub_vect(vect vect1, vect vect2){
    return add_vect(
        vect1, 
        scale_vect(vect2, -1)
    );
}

// absolute distance of vector from origin
float length(vect vect1){
    return sqrt(vect1.x*vect1.x + vect1.y*vect1.y);
}

// absolute distance between two vectors
float dist(vect vect1, vect vect2){
    return length(sub_vect(vect1, vect2));
}

bool equals_vect(vect vect1, vect vect2){
    if((int)vect1.x == (int)vect2.x && (int)vect1.y == (int)vect2.y)
        return true;
    return false;
}