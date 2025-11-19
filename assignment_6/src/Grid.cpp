#include "../lib/Grid.hpp"

Grid::Grid( size_t rows, size_t columns , Vector4 windowSize ) {
    this->rows = rows;
    this->columns = columns;
    this->cellColumnSize = ( float )windowSize.z / ( float )rows;
    this->cellRowSize = ( float )windowSize.w / ( float )columns;

    Cell::cellSize = Vector2{ cellRowSize , cellColumnSize };

    gridDividers = new Edges();
    pathFactory = new PathFactory();
    cellFactory = new CellFactory();

    for ( size_t index = 0 ; index <= rows ; index++ ) {
        gridDividers->AddEdge( Vector2{ 0 , index * cellRowSize } , Vector2{ ( float )windowSize.z , index * cellRowSize }  );
    }
    for ( size_t index = 0 ; index <= columns ; index++ ) {
        gridDividers->AddEdge( Vector2{ index * cellColumnSize , 0 } , Vector2{ index * cellColumnSize , ( float )windowSize.w }  );
    }

    for ( size_t row = 0 ; row < rows ; row++ ) {
        std::vector< Cell * > aux;
        for ( size_t column = 0 ; column < columns ; column++ ) {
            aux.push_back( cellFactory->CreateCell( EMPTY , IntVector2{ row , column } ) );
        }
        grid.push_back( aux );
        aux.clear();
    }
    

}

Grid::~Grid() {
    grid.clear();
    delete gridDividers;
    delete pathFactory;
    delete cellFactory;
}

void Grid::Draw() {
    for ( size_t row = 0 ; row < rows ; row++ ) {
        for ( size_t column = 0 ; column < columns ; column++ ) {
            grid[row][column]->Draw();
        }
    }
    for ( size_t index = 0 ; index < paths.size() ; index++ ) {
        paths[index]->Draw( cellRowSize , cellColumnSize );
    }
    gridDividers->Draw( EDGE_MENU_COLOR );
}

void Grid::Input( Vector2 mousePosition , INPUT_ACTION input ) {
    auto findRow = [this]( Vector2 mousePosition ) {
        if( std::abs( mousePosition.y / cellRowSize ) >= rows ) {
            return ( float ) rows - 1;
        } else {
            return std::abs( mousePosition.y / cellRowSize );
        }
    };
    auto findColumn = [this]( Vector2 mousePosition ) {
        if( std::abs( mousePosition.x / cellColumnSize ) >= columns ) {
            return ( float ) columns - 1;
        } else {
            return std::abs( mousePosition.x / cellColumnSize );
        }
    };
    size_t row = findRow( mousePosition );
    size_t column = findColumn( mousePosition );
    

    switch ( input ) {
        case LEFT_CLICK:
            DeleteCell( row , column );
            grid[row][column] = cellFactory->CreateCell( OBSTACLE , IntVector2{ row , column } );
            RecalculatePath();
            break;
        case RIGHT_CLICK:
            DeleteCell( row , column );
            grid[row][column] = cellFactory->CreateCell( EMPTY , IntVector2{ row , column } );
            RecalculatePath();
            break;
        case MIDDLE_CLICK:
            if( !addingPath ) {
                addingPath = !addingPath;
                startPath = std::make_pair( row ,column );
            } else {
                addingPath = !addingPath;
                DeleteCell( startPath.first , startPath.second );
                grid[startPath.first][startPath.second] = cellFactory->CreateCell( START , IntVector2{ startPath.first , startPath.second } );
                DeleteCell( row , column );
                grid[row][column] = cellFactory->CreateCell( END , IntVector2{ row , column } );
                paths.push_back( pathFactory->Create( startPath , std::make_pair( row ,column ) ) );
                RecalculatePath();
            }
            break;
        case BUTTON_ONE_CLICK:
        case BUTTON_TWO_CLICK:
        case NONE:
            std::cout << "Not Implemented" << std::endl;
            break;
        default:
            break;
    }
}

void Grid::DeleteCell( size_t row , size_t column ) {
    if( nullptr == dynamic_cast<End*>(grid[row][column]) || nullptr == dynamic_cast<Start*>(grid[row][column]) ) {
        for ( size_t index = 0 ; index < paths.size() ; index++ ) {
            if( paths.size() == 0 ) {
                continue;
            }
            if( paths[index]->GetEnd().first == row && paths[index]->GetEnd().second == column ) {
                delete grid[paths[index]->GetStart().first][paths[index]->GetStart().second];
                grid[paths[index]->GetStart().first][paths[index]->GetStart().second] = cellFactory->CreateCell( EMPTY, IntVector2{ row , column });
                delete paths[index];
                paths.erase( paths.begin() + index );
                break;
            }
            if( paths[index]->GetStart().first == row && paths[index]->GetStart().second == column ) {
                delete grid[paths[index]->GetEnd().first][paths[index]->GetEnd().second];
                grid[paths[index]->GetEnd().first][paths[index]->GetEnd().second] = cellFactory->CreateCell( EMPTY , IntVector2{ row , column });
                delete paths[index];
                paths.erase( paths.begin() + index );
                break;
            }
        }
    }
    delete grid[row][column];
}

void Grid::RecalculatePath(){
    for ( size_t index = 0 ; index < paths.size() ; index++ ) {
        paths[index]->Compute( grid );
    }   
}