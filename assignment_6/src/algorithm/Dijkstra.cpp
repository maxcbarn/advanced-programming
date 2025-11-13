#include "../../lib/algorithm/Dijkstra.hpp"

Dijkstra::Dijkstra( std::pair< size_t , size_t> start , std::pair< size_t , size_t> end , std::vector< std::vector< Cell * > > grid ) {
    size_t rows = grid.size() , columns = grid.at( 0 ).size() ;
    std::vector< size_t > pathRowsColumns;
    std::vector< std::vector < int > > dist =  std::vector< std::vector < int > >( rows , std::vector < int >( columns , __INT_MAX__ ) );
    std::vector< std::vector < int > > prev =  std::vector< std::vector < int > >( rows , std::vector < int >( columns , -1 ) );
    std::vector< std::vector < bool > > visited =  std::vector< std::vector < bool > >( rows , std::vector < bool >( columns , false ) );
    dist[start.first][start.second] = 0;
    dist[start.first][start.second] = true;
    prev[start.first][start.second] = start.second + rows * start.first;
    
    for ( size_t row = 0 ; row < rows ; row++ ) {
        for ( size_t column = 0 ; column < columns ; column++ ) {
            if( grid[row][column]->BlocksPath() ) {
                visited[ row ][ column ] = true;
            }
        }
    }
    
    int indexVertex, row, column;

    for ( size_t index = 0 ; index < rows * columns ; index++ ){
        indexVertex = -1;
        for (size_t itVertex = 0 ; itVertex < rows * columns ; itVertex++ ) {
            row = itVertex / rows;
            column = itVertex % rows;
            if( !visited[ row ][ column ] && ( indexVertex == -1 || dist[ row ][ column ] < dist[ indexVertex / rows ][ indexVertex % rows ] ) ) {
                indexVertex = itVertex;
            }
        }

        if( indexVertex == -1 || dist[ indexVertex / rows ][ indexVertex % rows ] == __INT_MAX__ ) {
            break;
        }

        row = indexVertex / rows;
        column = indexVertex % rows;
        visited[ row ][ column ] = true;

        if( row <= (int)rows - 2 && ( dist[ row ][ column ] + 1 < dist[ row + 1 ][ column ] ) ) {
            dist[ row + 1 ][ column ] = dist[ row ][ column ] + 1;
            prev[ row + 1 ][ column ] = row * rows + column;
        }
        if( column <= (int)columns - 2 && ( dist[ row ][ column ] + 1 < dist[ row ][ column + 1 ] ) ) {
            dist[ row ][ column + 1 ] = dist[ row ][ column ] + 1;
            prev[ row ][ column + 1 ] = row * rows + column;
        }
        if( row > 0 && ( dist[ row ][ column ] + 1 < dist[ row - 1 ][ column ] ) ) {
            dist[ row - 1 ][ column ] = dist[ row ][ column ] + 1;
            prev[ row - 1 ][ column ] = row * rows + column;
        }
        if( column > 0 && ( dist[ row ][ column ] + 1 < dist[ row ][ column - 1 ] ) ) {
            dist[ row ][ column - 1 ] = dist[ row ][ column ] + 1;
            prev[ row ][ column - 1 ] = row * rows + column;
        }
    }
    
    if( dist[ end.first ][ end.second ] != __INT_MAX__ ) {  
        row = end.first;
        column = end.second;
        while ( row != (int)start.first || column != (int)start.second ) {
            pathRowsColumns.push_back( row );
            pathRowsColumns.push_back( column );
            indexVertex = prev[ row ][ column ];
            row = indexVertex / rows;
            column = indexVertex % rows;
        }
        pathRowsColumns.push_back( row );
        pathRowsColumns.push_back( column );
    }

    this->path = pathRowsColumns; 
}

Dijkstra::~Dijkstra() {
    path.clear();
}

std::vector< size_t > Dijkstra::GetPath() {
    return path;
}