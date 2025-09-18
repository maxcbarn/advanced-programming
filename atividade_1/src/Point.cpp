#include "../lib/Point.hpp"



Point::Point( float x , float y , Constrains * constrains , Color color , int radius ) : Dot( x , y , constrains ) {
    
    this->radius = radius;
    this->color = color;
}

Point::~Point() {
}

void Point::Draw() {
    DrawCircleV( position , radius , color );   
}

