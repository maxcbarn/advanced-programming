#include "../lib/Vertex.hpp"

Vertex::Vertex( float x , float y , Constrains * constrains , int width , Color color ) : Dot( x , y , constrains )
{
    position.x = x;
    position.y = y;
    this->color = color;
    this->width = width;
}

Vertex::~Vertex() {
}

Vector2 Vertex::GetEndVertexPosition() {
    if( endVertex != nullptr ) {
        return endVertex->GetPosition();
    } else {
        Vector2 n;
        n.x = -1;
        n.y = -1;
        return n;
    }
}

Vertex* Vertex::GetEndVertex() {
    return endVertex;
}

void Vertex::SetEndVertex( Vertex * vertex ) {
    endVertex = vertex;
}

void Vertex::Draw() {
    DrawLineEx( position , endVertex->GetPosition() , ( float )width , color );
}


