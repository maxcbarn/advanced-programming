#include "obstacle/Mud.hpp"

Mud::Mud( Size_t2 position ) : Obstacle( position ) {
    this->color = BROWN;
    this->cost = 4;
}

Mud::~Mud() {
    
}