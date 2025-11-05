#include "../lib/Edges.hpp"

Edges::Edges() {

}
Edges::~Edges() {
    edges.clear();
}
void Edges::AddEdge( Vector2 start , Vector2 end ) {
    edges.push_back( std::make_pair( start , end ) );
}

void Edges::RemoveEdge( Vector2 position ) {
    size_t indexToRemove = SearchEdge( position );
    std::vector< std::pair< Vector2 , Vector2 > > aux; 
    if( indexToRemove == edges.size() + 1 ) {
        return;
    }
    for ( size_t index = 0 ; index < edges.size() ; index++ ) {
        if( index == indexToRemove ) {
            continue;
        }
        aux.push_back( edges.at( index ) );
    }
    edges.clear();
    edges.assign( aux.begin() , aux.end() );
    aux.clear();
}

size_t Edges::SearchEdge( Vector2 position ) {
    auto distanceBetweenLineAndPoint = []( Vector2 start , Vector2 end , Vector2 point ) {
        return std::abs( ( ( end.y - start.y ) * point.x ) - ( ( end.x - start.x ) * point.y ) + ( end.x * start.y ) - ( end.y * start.x ) ) / std::sqrt( std::powf( end.y - start.y , 2 ) + std::powf( end.x - end.y , 2 ) );
    };
    bool aux = true;
    for ( size_t index = 0 ; index < edges.size() ; index++ ) {
        aux = true;
        aux = aux && distanceBetweenLineAndPoint( edges.at( index ).first , edges.at( index ).second , position ) <= EDGE_WIDTH; 
        aux = aux && ( ( edges.at( index ).first.x <= position.x && edges.at( index ).second.x >= position.x ) || ( edges.at( index ).first.x >= position.x && edges.at( index ).second.x <= position.x ) );
        aux = aux && ( ( edges.at( index ).first.y <= position.y && edges.at( index ).second.y >= position.y ) || ( edges.at( index ).first.y >= position.y && edges.at( index ).second.y <= position.y ) );
        if( aux ) {
            return index;
        }
    }
    return edges.size() + 1;
}

void Edges::InputAction( MouseButton mouseButton ) {
    if( mouseButton == MOUSE_BUTTON_RIGHT ) {
        RemoveEdge( GetMousePosition() );
        return;
    }
}

void Edges::Draw() {
    for ( size_t index = 0 ; index < edges.size() ; index++ ) {
        DrawLineEx( edges.at( index ).first , edges.at( index ).second , EDGE_WIDTH , EDGE_COLOR );
    }
}