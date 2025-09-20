#include "../lib/Sides.hpp"

Sides::Sides(){

}

Sides::~Sides(){
    for ( int index = 0 ; index < ( int )vertexs.size() ; index++ ) {
        vertexs.at( index ).reset();
    }
    vertexs.clear();
    polys.clear();
}

void Sides::CreateSide( Vector2 startPosition , Vector2 endPosition , Constrains * constrains , Color color , int width ) {
    Vertex * startVertex = Search( startPosition );
    Vertex * endVertex = Search( endPosition );

    if ( startVertex != nullptr && endVertex != nullptr ) {
        startVertex->SetEndVertex( endVertex );
    }

    if( startVertex == nullptr ) {
        vertexs.push_back( std::make_unique<Vertex>( startPosition , constrains , width , color ) );
        startVertex = vertexs.back().get();
    }
    if( endVertex == nullptr ) {
        vertexs.push_back( std::make_unique<Vertex>( endPosition , constrains , width , color ) );
        endVertex = vertexs.back().get();
        endVertex->SetEndVertex( nullptr );
    }
    
    startVertex->SetEndVertex( endVertex );
    if( IsAPoly( startVertex ) ) {
        AddPoly( startVertex );
    }
}

Vertex * Sides::Search( Vector2 position ) {
    Vector2 searchPosition;
    for ( int index = 0 ; index < ( int )vertexs.size() ; index++ ) {
        searchPosition = vertexs.at( index ).get()->GetPosition();
        if( searchPosition.x == position.x && searchPosition.y == position.y ) {
            return vertexs.at( index ).get();
        }
    }
    return nullptr;
}

void Sides::Draw( ) {
    Vertex * crawler, * root;
    for ( int index = 0 ; index < ( int )vertexs.size() ; index++ ) {
        if ( vertexs.at( index ).get()->GetEndVertex() != nullptr ) {
            vertexs.at( index ).get()->Draw();
        }
    }
    for ( int index = 0 ; index < ( int )polys.size() ; index++ ) {
        root = polys.at( index );
        crawler = root;
        do {
            DrawTriangle( crawler->GetEndVertex()->GetEndVertexPosition() , crawler->GetEndVertexPosition() , crawler->GetPosition() , polysColor.at( index ) );
            crawler = crawler->GetEndVertex()->GetEndVertex();
        } while ( crawler != root );        
    }
}

bool Sides::ClickInputAction( Vector2 mousePosition , Color color ) {
    Vertex * startVertex = SearchSide( mousePosition );
    int polyIndex;
    if( startVertex != nullptr ) {
        startVertex->ChangeColor( color );
        return true;
    }

    polyIndex = SearchPoly( mousePosition ); 
    if ( polyIndex != -1 ) {
        polysColor.at( polyIndex ) = color;
    }
    return false;
}

Vertex * Sides::SearchSide( Vector2 mousePosition ) {
    auto distanceBetweenLineAndPoint = []( Vector2 start , Vector2 end , Vector2 point ) {
        return std::abs( ( ( end.y - start.y ) * point.x ) - ( ( end.x - start.x ) * point.y ) + ( end.x * start.y ) - ( end.y * start.x ) ) / std::sqrt( std::powf( end.y - start.y , 2 ) + std::powf( end.x - end.y , 2 ) );
    };
    float width;
    Vector2 startPoint, endPoint;
    for ( int index = 0 ; index < ( int )vertexs.size() ; index++ ) {
        if ( vertexs.at( index ).get()->GetEndVertex() != nullptr ) {
            startPoint = vertexs.at( index ).get()->GetPosition();
            endPoint = vertexs.at( index ).get()->GetEndVertexPosition();
            width = vertexs.at( index ).get()->GetWidth();
            if( !( distanceBetweenLineAndPoint( startPoint , endPoint , mousePosition ) <= width / 2 ) ) { continue; }
            if( !( ( startPoint.x >= mousePosition.x && endPoint.x <= mousePosition.x ) || ( startPoint.x <= mousePosition.x && endPoint.x >= mousePosition.x ) || ( std::abs( startPoint.x - endPoint.x ) < width ) ) ) { continue; }
            if( !( ( startPoint.y >= mousePosition.y && endPoint.y <= mousePosition.y ) || ( startPoint.y <= mousePosition.y && endPoint.y >= mousePosition.y ) ||  ( std::abs( startPoint.y - endPoint.y ) < width ) ) ) { continue; }
            return vertexs.at( index ).get();
        } else {
            continue;
        }
    }
    return nullptr;
}

int Sides::SearchPoly( Vector2 mousePosition ) {
    Vertex * crawler, *root;
    Vector2 startPoint, endPoint;
    for ( int index = 0 ; index < ( int )polys.size() ; index++ ) {
        root = polys.at( index );
        crawler = root; 
        do {
            startPoint = crawler->GetPosition();
            endPoint = crawler->GetEndVertexPosition();
            if( !( startPoint.x >= mousePosition.x && endPoint.x <= mousePosition.x ) || ( startPoint.x <= mousePosition.x && endPoint.x >= mousePosition.x ) ){
                break;
            }
            if( !( startPoint.y >= mousePosition.y && endPoint.y <= mousePosition.y ) || ( startPoint.y <= mousePosition.y && endPoint.y >= mousePosition.y ) ){
                break;
            }
            crawler = crawler->GetEndVertex();
        } while ( crawler != root );
        if( crawler == root ) {
            return index;
        }
    }
    return -1;
}

bool Sides::IsAPoly( Vertex * vertex ) {
    Vertex * crawler = vertex->GetEndVertex();
    while ( crawler != nullptr && crawler != vertex ) {
        crawler = crawler->GetEndVertex();
    }
    if( crawler == nullptr ) {
        return false;
    }
    return true;
}

void Sides::AddPoly( Vertex * vertex ) {
    polys.push_back( vertex );
    polysColor.push_back( YELLOW );
}