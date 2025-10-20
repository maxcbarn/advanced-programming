#include "../lib/Points.hpp"

Points::Points() {

}

Points::~Points() {
    points.clear();
}

void Points::AddPoint( Vector2 point ) {
    points.push_back( point );
}

void Points::Draw( ) {
    for ( size_t index = 0 ; index < points.size() ; index++ ) {
        DrawCircleV( points.at( index ) , POINT_RADIUS , POINT_COLOR );
    }
}

size_t Points::SearchPoint( Vector2 position ) {
    for ( size_t index = 0 ; index < points.size() ; index++ ) {
        if( std::abs( position.x - points.at( index ).x ) <= POINT_RADIUS && std::abs( position.y - points.at( index ).y ) <= POINT_RADIUS ) {
            return index;
        }
    }
    return points.size() + 1;
}

void Points::RemovePoint( Vector2 position ) {
    size_t indexToRemove = SearchPoint( position );
    std::vector< Vector2 > aux; 
    if( indexToRemove == points.size() + 1 ) {
        return;
    }
    for ( size_t index = 0 ; index < points.size() ; index++ ) {
        if( index == indexToRemove ) {
            continue;
        }
        aux.push_back( points.at( index ) );
    }
    points.clear();
    points.assign( aux.begin() , aux.end() );
    aux.clear();
}

void Points::InputAction( MouseButton input ) {
    if( input == MOUSE_BUTTON_LEFT ) {
        AddPoint( GetMousePosition() );
        return;
    }
    if( input == MOUSE_BUTTON_RIGHT ) {
        RemovePoint( GetMousePosition() );
        return;
    }
}
