#include "obstacle/Wall.hpp"

Wall::Wall( Size_t2 position ) : Obstacle( position ) {
    this->color = GRAY;
    this->cost = INT_MAX;
}

Wall::~Wall() {
    
}