#include "../../lib/path/ExactPath.hpp"

ExactPath::ExactPath( std::pair< size_t , size_t> start , std::pair< size_t , size_t > end ) : Path( start , end ) {

}

ExactPath::~ExactPath() {
    pathRowsColumns.clear();
}

void ExactPath::Draw( float cellRowSize , float cellColumnSize ) {
    if( pathRowsColumns.size() == 0 ) {
        return;
    }
    Vector2 start, end; 
    for ( size_t index = 2 ; index < pathRowsColumns.size() ; index = index + 2 ) {
        start = Vector2{ pathRowsColumns[ index - 1 ] * cellRowSize + cellRowSize / 2 , pathRowsColumns[ index - 2 ] * cellColumnSize + cellColumnSize / 2 };
        end = Vector2{ pathRowsColumns[ index + 1 ] * cellRowSize + cellRowSize / 2 , pathRowsColumns[ index ] * cellColumnSize + cellColumnSize / 2 };
        DrawLineEx( start , end , EDGE_WIDTH , EDGE_PATH_COLOR );
    }
}

void ExactPath::Compute( std::vector< std::vector< Cell * > > grid ) {
    PathFinding * algorithPathFinding = pathFindingFactory->Create( EXACT );
    pathRowsColumns = algorithPathFinding->FindPath( start , end , grid );
    delete algorithPathFinding;
}