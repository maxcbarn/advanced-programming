#include "../../lib/grid/CellFactory.hpp"

CellFactory::CellFactory( Vector2 cellSize ) {
    this->cellSize = cellSize;
}

CellFactory::~CellFactory() {

}

Cell * CellFactory::CreateCell( CELL_STATUS cell , IntVector2 position  ) {
    switch ( cell ) {
        case EMPTY:
            return ( Cell * ) new Empty( cellSize , position );
        case OBSTACLE:
            return ( Cell * ) new Obstacle( cellSize , position );
        case START:
            return ( Cell * ) new Start( cellSize , position );
        case END:
            return ( Cell * ) new End( cellSize , position );
    }
    return nullptr;
}