#include "../lib/Point.hpp"

Point::Point( Vector2 position , Constrains * constrains , Color color , int radius ) : Dot( position , constrains , color ) {
    this->radius = radius;
}

Point::~Point() {
}

void Point::Draw() {
    DrawCircleV( position , radius , color );   
}

int Point::GetRaius() {
    return radius;
}

