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
    }

    for ( size_t index = 0 ; index < startVertex->GetNextVertex().size() ; index++ ) {
        if( startVertex->GetNextVertex().at( index ) == endVertex ) {
            return;
        }
    }
    startVertex->AddEndVertex( endVertex );
    endVertex->AddEndVertex( startVertex );
    CreatePolys( SearchReturnIndex( startVertex ) );
}

Vertex * Sides::Search( Vector2 position ) {
    Vector2 searchPosition;
    for ( size_t index = 0 ; index < vertexs.size() ; index++ ) {
        searchPosition = vertexs.at( index ).get()->GetPosition();
        if( searchPosition.x == position.x && searchPosition.y == position.y ) {
            return vertexs.at( index ).get();
        }
    }
    return nullptr;
}

size_t Sides::SearchReturnIndex( Vertex * vertex ) {
    for ( size_t index = 0 ; index < vertexs.size() ; index++ ) {
        if( vertexs.at( index ).get() == vertex ) {
            return index;
        }
    }
    std::cout << "Vertex Not In The Right Place\n";
    exit(0);
}

void Sides::Draw( ) {
    for ( size_t index = 0 ; index < vertexs.size() ; index++ ) {
        vertexs.at( index ).get()->Draw();
    }
}

bool Sides::ClickInputAction( MouseButton mouseButton , Vector2 mousePosition , Color color ) {
    std::tuple< Vertex * , Vertex * > side = SearchSide( mousePosition );
    
    if( std::get<0>(side) != nullptr ) {
        if( mouseButton == MOUSE_BUTTON_LEFT ){
            std::cout << "Point 1: (" << std::get<0>( side )->GetPosition().x << "," << std::get<0>( side )->GetPosition().y << ") Point 2: (" << std::get<1>( side )->GetPosition().x << "," << std::get<1>( side )->GetPosition().y << ")\n";
        }
        if( mouseButton == MOUSE_BUTTON_RIGHT ) {
            DeleteSides(  std::get<0>( side ) ,  std::get<1>( side ) );
        }
        return true;
    }
    return false;
}


std::tuple< Vertex * , Vertex * > Sides::SearchSide( Vector2 mousePosition ) {
                                                        
                                                  /*  ⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⣤⣶⣶⣶⣶⣶⣤⣄⡀⠀⠀⠀⠀⠀⠀
                                                    ⠀⠀⠀⠀⠀⠀⣠⣴⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⣄⡀⠀⠀⠀⠀⠀
                                                    ⠀⠀⠀⣠⣴⣴⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣮⣵⣄⠀⠀⠀
                                                    ⠀⠀⢾⣻⣿⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢿⣿⣿⡀⠀
                                                    ⠀⠸⣽⣻⠃⣿⡿⠋⣉⠛⣿⣿⣿⣿⣿⣿⣿⣿⣏⡟⠉⡉⢻⣿⡌⣿⣳⡥⠀
                                                    ⠀⢜⣳⡟⢸⣿⣷⣄⣠⣴⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⣤⣠⣼⣿⣇⢸⢧⢣⠀
                                                    ⠀⠨⢳⠇⣸⣿⣿⢿⣿⣿⣿⣿⡿⠿⠿⠿⢿⣿⣿⣿⣿⣿⣿⣿⣿⠀⡟⢆⠀
                                                    ⠀⠀⠈⠀⣾⣿⣿⣼⣿⣿⣿⣿⡀⠀⠀⠀⠀⣿⣿⣿⣿⣿⣽⣿⣿⠐⠈⠀⠀
                                                    ⠀⢀⣀⣼⣷⣭⣛⣯⡝⠿⢿⣛⣋⣤⣤⣀⣉⣛⣻⡿⢟⣵⣟⣯⣶⣿⣄⡀⠀
                                                    ⣴⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣶⣶⣶⣾⣶⣶⣴⣾⣿⣿⣿⣿⣿⣿⢿⣿⣿⣧
                                                    ⣿⣿⣿⠿⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⠿⣿⡿ */
                                                    
    auto distanceBetweenLineAndPoint = []( Vector2 start , Vector2 end , Vector2 point ) {
        return std::abs( ( ( end.y - start.y ) * point.x ) - ( ( end.x - start.x ) * point.y ) + ( end.x * start.y ) - ( end.y * start.x ) ) / std::sqrt( std::powf( end.y - start.y , 2 ) + std::powf( end.x - end.y , 2 ) );
    };
    float width;
    Vector2 startPoint, endPoint;
    for ( int index = 0 ; index < ( int )vertexs.size() ; index++ ) {
        for ( size_t endVertexIndex = 0 ; endVertexIndex < vertexs.at( index ).get()->GetNextVertex().size() ; endVertexIndex++ ) {
            startPoint = vertexs.at( index ).get()->GetPosition();
            endPoint = vertexs.at( index ).get()->GetNextVertex()[endVertexIndex]->GetPosition();
            width = vertexs.at( index ).get()->GetWidth();
            if( !( distanceBetweenLineAndPoint( startPoint , endPoint , mousePosition ) <= width / 2 ) ) { continue; }
            if( !( ( startPoint.x >= mousePosition.x && endPoint.x <= mousePosition.x ) || ( startPoint.x <= mousePosition.x && endPoint.x >= mousePosition.x ) || ( std::abs( startPoint.x - endPoint.x ) < width ) ) ) { continue; }
            if( !( ( startPoint.y >= mousePosition.y && endPoint.y <= mousePosition.y ) || ( startPoint.y <= mousePosition.y && endPoint.y >= mousePosition.y ) ||  ( std::abs( startPoint.y - endPoint.y ) < width ) ) ) { continue; }
            return std::make_tuple( vertexs.at( index ).get() , vertexs.at( index ).get()->GetNextVertex()[endVertexIndex] );
        }
    }
    return std::make_tuple( nullptr , nullptr );
}

void Sides::DeleteSides( Vertex * start , Vertex * end ) {
    CheckDeletionSidePolys( start , end );
    start->RemoveEndVertex( end );
    end->RemoveEndVertex( start );
    std::cout << polys.size() << "\n";
}

void Sides::CheckDeletionSidePolys( Vertex * start , Vertex * end ) {
    size_t count = 0 ;
    std::deque< Vertex * > aux; 
    for ( size_t index = 0 ; index < polys.size() ; index++ ) {
        aux = polys.front();
        for ( size_t indexPoly = 0 ; indexPoly < aux.size() ; indexPoly++ ) {
            if( aux.at( indexPoly ) == start || aux.at( indexPoly ) == end ) {
                count++;
            }
        }
        if( count == 2 ) {
            polys.pop_front();
        } else {
            polys.push_back( polys.front() );
        }
        count = 0;
    }
}

void Sides::DeleteVertex( Vertex * vertex ) {
    for ( size_t index = 0 ; index < vertexs.size() ; index++ ) {
        if( vertexs.front().get() == vertex ) {
            vertexs.pop_front();
            break;
        } else {
            vertexs.push_back( std::move( vertexs.front() ) );
            vertexs.pop_front();
        }
    }
}
/*

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
}*/

int Sides::GetVertexQuantity() {
    return vertexs.size();
}

void Sides::CreatePolys( size_t index ) {    
    std::vector< bool > bitMap( vertexs.size() , false );
    std::deque< Vertex * > backTrack;
    DeepFirstSearch( index , bitMap , backTrack , nullptr );
    std::cout << polys.size() << "\n";
}

void Sides::AddPoly( std::deque< Vertex * > poly ) {
    size_t indexPoly;
    if( poly.size() < 3 ) {
        return;
    }
    for ( size_t index = 0 ; index < polys.size() ; index++ ) {
        if( poly.size() != polys.at( index ).size() ) {
            continue;
        } 
        for ( indexPoly = 0 ; indexPoly < polys.at( index ).size() ; indexPoly++ ) {
            if( poly.at( indexPoly ) != polys.at( index ).at( indexPoly ) ) {
                break;
            }
        }
        if( indexPoly == polys.at( index ).size() ) {
            return;
        }
    }
    polys.push_back( poly );
}

void Sides::DeepFirstSearch( size_t index , std::vector< bool > &bitMap , std::deque< Vertex * > &backTrack , Vertex * lastVertex ) {
    size_t nextIndex;
    bitMap[ index ] = true;
    backTrack.push_back( vertexs.at( index ).get() );

    for ( size_t indexEndVertex = 0 ; indexEndVertex < vertexs.at( index ).get()->GetNextVertex().size() ; indexEndVertex++ ) {
        nextIndex = SearchReturnIndex( vertexs.at( index ).get()->GetNextVertex().at( indexEndVertex ) );
        if( vertexs.at( nextIndex ).get() == lastVertex ) {
            continue;
        }   
        if( bitMap[nextIndex] ) {
            AddPoly( backTrack );
        } else {
            DeepFirstSearch( nextIndex , bitMap , backTrack , vertexs.at( index ).get() );
        }
    }
    backTrack.pop_back();
}