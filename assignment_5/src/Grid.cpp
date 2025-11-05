#include "../lib/Grid.hpp"

Grid::Grid( size_t rows , size_t columns )  {
    this->rows = rows;
    this->columns = columns;

    std::vector< CELL_STATUS > auxVector;

    for ( size_t i = 0 ; i < rows ; i++ ) {
        for ( size_t i = 0; i < columns ; i++ )
        {
            auxVector.push_back( EMPTY );
        }
        cells.push_back( auxVector );
        auxVector.clear();
    }
}

CELL_STATUS Grid::GetCellStatus( size_t row , size_t column ) {
    return cells[ row ][ column ]; 
}

void Grid::SetCellStatus( size_t row , size_t column , CELL_STATUS cellStatus ) {
    cells[ row ][ column ] = cellStatus; 
}

Grid::~Grid() {
    for ( size_t i = 0 ; i < rows ; i++ ) {
        cells[ i ].clear();
    }
    cells.clear();
}