#include "../../lib/grid/Cell.hpp"


Cell:: Cell( IntVector2 position ){
    this->position = position;
    this->blocksPath = false;
};

bool Cell::BlocksPath() {
    return blocksPath;
};

void Cell::Draw() {
    return;
}