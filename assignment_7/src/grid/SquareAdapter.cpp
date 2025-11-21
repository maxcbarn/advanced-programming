#include "grid/SquareAdapter.hpp"

SquareAdapter::SquareAdapter(  size_t rows , size_t columns , Vector4 windowSize  ) : GridAdapter( rows , columns , windowSize ) {
    this->rowSize = windowSize.z / ( float )rows;
    this->columnSize = windowSize.w / ( float )columns;
}

SquareAdapter::~SquareAdapter() {

}

Vector2 SquareAdapter::GetCentroidOfCell( Size_t2 position ) {
    Vector2 centroid;
    centroid.x = rowSize * position.x + rowSize / 2;
    centroid.y = columnSize * position.y + columnSize / 2;
    return centroid;
} 

float SquareAdapter::GetRadiusOfCell( ){
    if( rowSize < columnSize ) {
        return rowSize / 2;
    } else {
        return columnSize / 2;
    }
}

std::vector< Size_t2 > SquareAdapter::WhoIsMyNeighburs( Size_t2 position ) {
    std::vector< Size_t2 > neighburs;
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

void SquareAdapter::DrawGrid() {
    Grid * grid = Grid::GetGrid();
    Vector2 start, end;
    
    grid->Draw();
    
    DrawLineEx( Vector2{ windowsSize.x , windowsSize.y } , Vector2{ windowsSize.z , windowsSize.y } , MENU_LINE_WIDTH , MENU_LINE_COLOR );
    DrawLineEx( Vector2{ windowsSize.x , windowsSize.y } , Vector2{ windowsSize.y , windowsSize.w } , MENU_LINE_WIDTH , MENU_LINE_COLOR );
    
    start = Vector2{ 0 , windowsSize.y };
    end = Vector2{ 0 , windowsSize.w };
    for ( size_t row = 1 ; row <= rows ; row++ ) {
        start.x = rowSize * row;
        end.x = rowSize * row;
        DrawLineEx( start , end , MENU_LINE_WIDTH , MENU_LINE_COLOR );
    }
    
    start = Vector2{ windowsSize.x , 0 };
    end = Vector2{ windowsSize.z , 0 };
    for ( size_t column = 1 ; column <= columns ; column++ ) {
        start.y = columnSize * column;
        end.y = columnSize * column;
        DrawLineEx( start , end , MENU_LINE_WIDTH , MENU_LINE_COLOR );
    }
}


void SquareAdapter::Input( INPUT_ACTION inputAction , Vector2 position ) {
    Size_t2 cellPosition;
    cellPosition.x = ( size_t )floorf( position.x / rowSize );
    cellPosition.y = ( size_t )floorf( position.y / columnSize );

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
