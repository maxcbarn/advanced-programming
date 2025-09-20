#include "../lib/Vertex.hpp"

Vertex::Vertex( Vector2 position , Constrains * constrains , int width , Color color ) : Dot( position , constrains , color )
{
    this->width = width;
}

Vertex::~Vertex() {
}

Vector2 Vertex::GetEndVertexPosition() {
    if( endVertex != nullptr ) {
        return endVertex->GetPosition();
    } else {
        return Vector2{ -1 , -1 };
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

int Vertex::GetWidth() {
    return width;
}


