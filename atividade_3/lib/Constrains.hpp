#ifndef CONSTRAINS_HPP
#define CONSTRAINS_HPP

#include "../lib/raylib.h"
#include <iostream>

typedef struct {
    int maxXPosition, maxYPosition, minXPosition , minYPosition;
    void Set( int maxXPosition , int maxYPosition , int minXPosition , int minYPosition ) {
        this->maxXPosition = maxXPosition;
        this->maxYPosition = maxYPosition;
        this->minXPosition = minXPosition;
        this->minYPosition = minYPosition;     
    }
} Constrains;

#endif