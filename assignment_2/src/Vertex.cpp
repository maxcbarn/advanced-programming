#include "../lib/Vertex.hpp"

Vertex::Vertex( Vector2 position , Constrains * constrains , int width , Color color ) : Dot( position , constrains , color )
{
    this->width = width;
}

Vertex::~Vertex() {
}

std::deque< Vertex * > Vertex::GetNextVertex() {
    return nextVertex;
}

void Vertex::RemoveEndVertex( Vertex * vertex ) {
    for ( size_t index = 0 ; index < nextVertex.size() ; index++ ) {
        if( nextVertex.front() == vertex ) {
            nextVertex.pop_front();
            break;
        } else {
            nextVertex.push_back( nextVertex.front() );
            nextVertex.pop_front();
        }
    }
}

void Vertex::AddEndVertex( Vertex * vertex ) {
    nextVertex.push_back( vertex );
}

void Vertex::Draw() {
    for ( size_t index = 0 ; index < nextVertex.size() ; index++ ) {
        DrawLineEx( position , nextVertex.at( index )->GetPosition() , ( float )width , color );
    }
}

int Vertex::GetWidth() {
    return width;
}

bool Vertex::IsEndVertex( Vertex * vertex ) {
    for ( size_t i = 0 ; i < nextVertex.size() ; i++ ) {
        if( nextVertex.at( i ) == vertex ) {
            return true;
        }
    }
    return false;
}

