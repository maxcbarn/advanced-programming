#include "grid/HexaAdapter.hpp"
#include "grid/Grid.hpp"

HexaAdapter::HexaAdapter(  size_t rows , size_t columns , Vector4 windowSize  ) : GridAdapter( rows , columns , windowSize ) {
    this->height = windowSize.w / ( ( float ) columns + 0.5 );
    this->width = height;
    this->offsetHeight = height / 2;
    this->offsetWidth = width / 2;
    if ( rows % 2 == 0 ) {
        this->centerOffset = ( windowsSize.z - ( width * rows / 2 + width * rows / 4 ) ) / 2 + width / 2;
    } else {
        this->centerOffset = ( windowsSize.z - ( width * ceilf( rows / 2 ) + width * floorf( rows / 2 ) / 2 ) ) / 2;
    }

    std::vector< Vector2 > aux; 
    Vector2 centroid;

    for ( size_t row = 0 ; row < rows ; row++ ) {
        for (size_t column = 0 ; column < columns ; column++ ) {
            if( row % 2 == 0 ) {
                centroid.x = ( row * width - width / 4 * row ) + centerOffset;
                centroid.y = column * height + height / 2;
            } else {
                centroid.x = ( row * width - width / 4 * row ) + centerOffset;
                centroid.y = column * height + height / 2 + offsetHeight;
            }
            aux.push_back( centroid );
        }
        centroids.push_back( aux );
        aux.clear();
    }
}

HexaAdapter::~HexaAdapter() {

}

Vector2 HexaAdapter::GetCentroidOfCell( Size_t2 position ) {
    return centroids[position.x][position.y];
} 

float HexaAdapter::GetRadiusOfCell( ){
    return width / 3.35;
}

std::vector< Size_t2 > HexaAdapter::WhoIsMyNeighburs( Size_t2 position ) {
    std::vector< Size_t2 > neighburs;

    if( position.x % 2 == 0 ) {
        if( position.x > 0 ) {
            neighburs.push_back( Size_t2{ position.x - 1 , position.y } );
            if( position.y > 0 ) {
                neighburs.push_back( Size_t2{ position.x - 1 , position.y - 1 } );
            }
        }
        if( position.x < rows - 1 ) {
            neighburs.push_back( Size_t2{ position.x + 1 , position.y } );
            if( position.y > 0 ) {
                neighburs.push_back( Size_t2{ position.x + 1 , position.y - 1 } );
            }
        }
        if( position.y > 0 ) {
            neighburs.push_back( Size_t2{ position.x , position.y - 1 } );
        }
        if( position.y < columns - 1 ) {
            neighburs.push_back( Size_t2{ position.x , position.y + 1 } );
        }

    } else {
        if( position.x > 0 ) {
            neighburs.push_back( Size_t2{ position.x - 1 , position.y } );
            if( position.y < columns - 1 ) {
                neighburs.push_back( Size_t2{ position.x - 1 , position.y + 1 } );
            }
        }
        if( position.x < rows - 1 ) {
            neighburs.push_back( Size_t2{ position.x + 1 , position.y } );
            if( position.y < columns - 1 ) {
                neighburs.push_back( Size_t2{ position.x + 1 , position.y + 1 } );
            }
        }
        if( position.y > 0 ) {
            neighburs.push_back( Size_t2{ position.x , position.y - 1 } );
        }
        if( position.y < columns - 1 ) {
            neighburs.push_back( Size_t2{ position.x , position.y + 1 } );
        }
    }

    if( position.x > 0 ) {
        neighburs.push_back( Size_t2{ position.x - 1 , position.y } );
    }

    if( position.x < rows - 1 ) {
        neighburs.push_back( Size_t2{ position.x + 1 , position.y } );
    }

    if( position.y > 0 ) {
        neighburs.push_back( Size_t2{ position.x , position.y - 1 } );
    }

    if( position.y < columns - 1 ) {
        neighburs.push_back( Size_t2{ position.x , position.y + 1 } );
    }
    return neighburs;
}

void HexaAdapter::DrawGrid() {
    Grid * grid = Grid::GetGrid();
    Vector2 p1, p2, p3, p4, p5, p6, centroid;
    
    grid->Draw();

    for ( size_t row = 0 ; row < rows ; row++ ) {
        for (size_t column = 0 ; column < columns ; column++ ) {
            centroid = GetCentroidOfCell( Size_t2{ row , column } );
            p1 = Vector2{ centroid.x - width / 2 , centroid.y };
            p2 = Vector2{ centroid.x - width / 4 , centroid.y + height / 2 };
            p3 = Vector2{ centroid.x + width / 4 , centroid.y + height / 2 };
            p4 = Vector2{ centroid.x + width / 2 , centroid.y };
            p5 = Vector2{ centroid.x + width / 4 , centroid.y - height / 2 };
            p6 = Vector2{ centroid.x - width / 4 , centroid.y - height / 2 };
            DrawLineEx( p1 , p2 , MENU_LINE_WIDTH , MENU_LINE_COLOR );
            DrawLineEx( p2 , p3 , MENU_LINE_WIDTH , MENU_LINE_COLOR );
            DrawLineEx( p3 , p4 , MENU_LINE_WIDTH , MENU_LINE_COLOR );
            DrawLineEx( p4 , p5 , MENU_LINE_WIDTH , MENU_LINE_COLOR );
            DrawLineEx( p5 , p6 , MENU_LINE_WIDTH , MENU_LINE_COLOR );
            DrawLineEx( p6 , p1 , MENU_LINE_WIDTH , MENU_LINE_COLOR );
        }    
    }
}


void HexaAdapter::Input( INPUT_ACTION inputAction , Vector2 position ) {
    Size_t2 cellPosition;
    auto distance = [](auto p1, auto p2) {
        return std::sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
    };

    if( position.x < centerOffset - width / 2 ) {
        return;
    }
    if( position.x > windowsSize.z - centerOffset + width / 2 ) {
        return;
    }

    double shortest = 10000000000;

    for ( size_t row = 0 ; row < rows ; row++ ) {
        for ( size_t column = 0 ; column < columns ; column++ ) {
            if( shortest > distance( position , GetCentroidOfCell( Size_t2{ row , column } ) ) ) {
                shortest = distance( position , GetCentroidOfCell( Size_t2{ row , column } ) );
                cellPosition = Size_t2{ row , column };
            }
        }
    }

    if( cellPosition.x > rows - 1 ) {
        cellPosition.x = rows - 1;
    }
    if( cellPosition.y > columns - 1 ) {
        cellPosition.y = columns - 1;
    }

    switch (inputAction)
    {
    case ADD_MUD:
        Grid::GetGrid()->AddObstacle( MUD , cellPosition );
        break;
    case ADD_WALL:
        Grid::GetGrid()->AddObstacle( WALL , cellPosition );
        break;
    case ADD_AGENT:
        Grid::GetGrid()->AddAgent( cellPosition );
        break;
    case REMOVE:
        Grid::GetGrid()->Remove( cellPosition );
        break;
    default:
        break;
    }
}
