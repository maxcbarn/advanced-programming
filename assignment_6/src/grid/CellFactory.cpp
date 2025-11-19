#include "../../lib/grid/CellFactory.hpp"

CellFactory::CellFactory() {
    
}

CellFactory::~CellFactory() {

}

Cell * CellFactory::CreateCell( CELL_STATUS cell , IntVector2 position  ) {
    switch ( cell ) {
        case EMPTY:
            return ( Cell * ) new Empty( position );
        case OBSTACLE:
            return ( Cell * ) new Obstacle( position );
        case START:
            return ( Cell * ) new Start( position );
        case END:
            return ( Cell * ) new End( position );
    }
    return nullptr;
}