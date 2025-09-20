#include "../lib/Dot.hpp"

Dot::Dot( Vector2 position , Constrains * constrains , Color color ) {
    this->position = position;
    this->constrains = constrains;
    this->color = color;
}

Dot::~Dot() {

}

void Dot::Move( Vector2 position ) {
    if( position.x > constrains->maxXPosition ) {
        position.x = constrains->maxXPosition;
    }
    if( position.x < constrains->minXPosition ) {
        position.x = constrains->minXPosition;
    }
    if( position.y > constrains->maxYPosition ) {
        position.y = constrains->maxYPosition;
    }
    if( position.y > constrains->minYPosition ) {
        position.y = constrains->minYPosition;
    }
    this->position.x = position.x;
    this->position.y = position.y;
}

Vector2 Dot::GetPosition() {
    return position;
}

void Dot::ChangeColor( Color color ) {
    this->color = color;
}