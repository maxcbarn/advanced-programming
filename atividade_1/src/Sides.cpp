#include "../lib/Sides.hpp"

Sides::Sides(){

}

Sides::~Sides(){
    for ( int index = 0 ; index < ( int )vertexs.size() ; index++ ) {
        vertexs.at( index ).reset();
    }
    vertexs.clear();
}

void Sides::CreateSide( Vector2 startPosition , Vector2 endPosition , Constrains * constrains , Color color , int width ) {
    Vertex * startVertex = Search( startPosition );
    Vertex * endVertex = Search( endPosition );

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
}

Vertex * Sides::Search( Vector2 position ) {
    Vector2 searchPosition;
    for ( int index = 0 ; index < ( int )vertexs.size() ; index++ ) {
        searchPosition = vertexs.at( index ).get()->GetPosition();
        if( searchPosition.x == position.x && searchPosition.y == position.y && vertexs.at( index ).get()->GetEndVertex() == nullptr ) {
            return vertexs.at( index ).get();
        }
    }
    return nullptr;
}

void Sides::Draw( ) {
    for ( int index = 0 ; index < ( int )vertexs.size() ; index++ ) {
        if ( vertexs.at( index ).get()->GetEndVertex() != nullptr ) {
            vertexs.at( index ).get()->Draw();
        }
    }
}

bool Sides::ClickInputAction( MouseButton mouseButton , Vector2 mousePosition , Color color ) {
    Vertex * startVertex = SearchSide( mousePosition );
    
    if( startVertex != nullptr ) {
        if( mouseButton == MOUSE_BUTTON_LEFT ){
            startVertex->ChangeColor( color );
        }
        if( mouseButton == MOUSE_BUTTON_RIGHT ) {
            DeleteSides( startVertex );
        }
        return true;
    }
    return false;
}

Vertex * Sides::SearchSide( Vector2 mousePosition ) {
                                                        /* 
                                                    ⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⣤⣶⣶⣶⣶⣶⣤⣄⡀⠀⠀⠀⠀⠀⠀
                                                    ⠀⠀⠀⠀⠀⠀⣠⣴⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⣄⡀⠀⠀⠀⠀⠀
                                                    ⠀⠀⠀⣠⣴⣴⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣮⣵⣄⠀⠀⠀
                                                    ⠀⠀⢾⣻⣿⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢿⣿⣿⡀⠀
                                                    ⠀⠸⣽⣻⠃⣿⡿⠋⣉⠛⣿⣿⣿⣿⣿⣿⣿⣿⣏⡟⠉⡉⢻⣿⡌⣿⣳⡥⠀
                                                    ⠀⢜⣳⡟⢸⣿⣷⣄⣠⣴⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⣤⣠⣼⣿⣇⢸⢧⢣⠀
                                                    ⠀⠨⢳⠇⣸⣿⣿⢿⣿⣿⣿⣿⡿⠿⠿⠿⢿⣿⣿⣿⣿⣿⣿⣿⣿⠀⡟⢆⠀
                                                    ⠀⠀⠈⠀⣾⣿⣿⣼⣿⣿⣿⣿⡀⠀⠀⠀⠀⣿⣿⣿⣿⣿⣽⣿⣿⠐⠈⠀⠀
                                                    ⠀⢀⣀⣼⣷⣭⣛⣯⡝⠿⢿⣛⣋⣤⣤⣀⣉⣛⣻⡿⢟⣵⣟⣯⣶⣿⣄⡀⠀
                                                    ⣴⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣶⣶⣶⣾⣶⣶⣴⣾⣿⣿⣿⣿⣿⣿⢿⣿⣿⣧
                                                    ⣿⣿⣿⠿⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⠿⣿⡿
                                                    */
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

void Sides::DeleteSides( Vertex * start ) {
    Vertex * endVertex = start->GetEndVertex();
    start->SetEndVertex( nullptr );
    if( !CheckVertex( endVertex ) ) {
        DeleteVertex( endVertex );
    }
    if( !CheckVertex( start ) ) {
        DeleteVertex( start );
    }
}

void Sides::DeleteVertex( Vertex * vertex ) {
    std::deque< std::unique_ptr< Vertex > > auxDeque;
    int indexElement;
    for ( indexElement = 0 ; indexElement < ( int )vertexs.size() ; indexElement++ ) {
        if( vertexs.at( indexElement ).get() == vertex ){
            break;
        }
    }
    for ( int index = 0 ; index <= indexElement ; index++) {
        auxDeque.push_back( std::move( vertexs.front() ) );
        vertexs.pop_front();
    }
    auxDeque.pop_back();
    for ( int index = 0 ; index < indexElement ; index++ ) {
        vertexs.push_front( std::move( auxDeque.back() ) );
        auxDeque.pop_back();
    }
}

bool Sides::CheckVertex( Vertex * vertex ) {
    if( vertex->GetEndVertex() != nullptr ) {
        return true;
    }
    for ( size_t index = 0 ; index < vertexs.size() ; index++ ) {
        if( vertexs.at( index ).get()->GetEndVertex() == vertex ) {
            return true;
        }
    }
    return false;   
}

int Sides::GetVertexQuantity() {
    return vertexs.size();
}

void CreatePolys() {    
}