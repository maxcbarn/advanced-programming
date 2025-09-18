#include "../lib/Sides.hpp"

Sides::Sides(){

}

Sides::~Sides(){
    
}

void Sides::CreateSide( float xStart , float yStart , float xEnd , float yEnd  , Constrains * constrains , Color color , int width , float xStartVelocity , float yStartVelocity, float xEndVelocity , float yEndVelocity ) {
    Vertex * startVertex = Search( xStart , yStart );
    Vertex * endVertex = Search( xEnd , yEnd );

    if ( startVertex != nullptr && endVertex != nullptr ) {
        startVertex->SetEndVertex( endVertex );
    }

    if( startVertex == nullptr ) {
        vertexs.push_back( std::make_unique<Vertex>( xStart , yStart , constrains , width , color ) );
        startVertex = vertexs.back().get();
    }
    if( endVertex == nullptr ) {
        vertexs.push_back( std::make_unique<Vertex>( xEnd , yEnd , constrains , width , color ) );
        endVertex = vertexs.back().get();
        endVertex->SetEndVertex( nullptr );
    }

    startVertex->SetVelocity( xStartVelocity , yStartVelocity );
    endVertex->SetVelocity( xEndVelocity , yEndVelocity );
    
    startVertex->SetEndVertex( endVertex );
}

Vertex * Sides::Search( float x , float y ) {
    Vector2 position;
    for ( int index = 0 ; index < ( int )vertexs.size() ; index++ ) {
        position = vertexs.at( index ).get()->GetPosition();
        if( position.x == x && position.y == y ) {
            return vertexs.at( index ).get();
        }
    }
    return nullptr;
}


void Sides::Draw( ) {
    for ( int index = 0 ; index < ( int )vertexs.size() ; index++ ) {
        vertexs.at( index ).get()->Move( 0 , 0 );
    }

    for ( int index = 0 ; index < ( int )vertexs.size() ; index++ ) {
        if ( vertexs.at( index ).get()->GetEndVertex() != nullptr ) {
            vertexs.at( index ).get()->Draw();
        }
    }
}