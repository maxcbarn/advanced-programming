#include "../lib/Points.hpp"

Points::Points() {
}

Points::~Points() {
    points.clear();
}

void Points::CreatePoint( float x , float y , Constrains * constrains , Color color , int radius , float xVelocity , float yVelocity ){
    points.push_back( std::make_unique< Point >( x , y , constrains , color , radius ) );
    points.back().get()->SetVelocity( xVelocity , yVelocity );
}

void Points::Draw() {
    for ( int index = 0 ; index < ( int )points.size() ; index++ ) {
        points[index].get()->Move( 0 , 0 );
        points[index].get()->Draw();
    }
}