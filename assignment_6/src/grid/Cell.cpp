#include "../../lib/grid/Cell.hpp"


Cell:: Cell( Vector2 cellSize , IntVector2 position ){
    this->cellSize = cellSize;
    this->position = position;
    this->blocksPath = false;
};

bool Cell::BlocksPath() {
    return blocksPath;
};

void Cell::Draw() {
    return;
}