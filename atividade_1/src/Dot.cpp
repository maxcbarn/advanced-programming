#include "../lib/Dot.hpp"

Dot::Dot( float x , float y , Constrains * constrains ) {
    position.x = x;
    position.y = y;
    this->constrains = constrains;
}

Dot::~Dot() {

}

void Dot::Move( float x , float y ) {
    if( velocity.x == 0 && velocity.y == 0 ) {
        if( x > constrains->maxXPosition ) {
            x = constrains->maxXPosition;
        }
        if( x < constrains->minXPosition ) {
            x = constrains->minXPosition;
        }
        if( y > constrains->maxYPosition ) {
            y = constrains->maxYPosition;
        }
        if( y > constrains->minYPosition ) {
            y = constrains->minYPosition;
        }
    } else {
        if( position.x + velocity.x > constrains->maxXPosition || position.x + velocity.x < constrains->minXPosition ) {
            if( position.x + velocity.x > constrains->maxXPosition ) {
                x = constrains->maxXPosition;
            } else {
                x = constrains->minXPosition;
            }
            velocity.x *= -1;
        } else {
            x = position.x + velocity.x;
        }
        if( position.y + velocity.y > constrains->maxYPosition || position.y + velocity.y < constrains->minYPosition ) {
            if( position.y + velocity.y > constrains->maxYPosition ) {
                y = constrains->maxYPosition;
            } else {
                y = constrains->minYPosition;
            }
            velocity.y *= -1;
        } else {
            y = position.y + velocity.y;
        }
    }
    position.x = x;
    position.y = y;
}


void Dot::SetVelocity( float x , float y ) {
    velocity.x = x;
    velocity.y = y;
}

Vector2 Dot::GetPosition() {
    return position;
}