#include "grid/Cell.hpp"

Cell::Cell( Size_t2 position ) {
    this->position = position;
}

Cell::~Cell() {

}

void Cell::Draw() {
    
}

Size_t2 Cell::GetPosition() {
    return position;
}