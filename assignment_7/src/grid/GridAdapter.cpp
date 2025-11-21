#include "grid/GridAdapter.hpp"

GridAdapter::GridAdapter( size_t rows , size_t columns , Vector4 windowSize ) {
    this->columns = columns;
    this->rows = rows;
    this->windowsSize = windowSize;
}

GridAdapter::~GridAdapter() {

}

Vector2 GridAdapter::GetCentroidOfCell( [[maybe_unused]] Size_t2 position ) {
    return Vector2{ 0 , 0 };
}

float GridAdapter::GetRadiusOfCell() {
    return 0;
}

std::vector< Size_t2 > GridAdapter::WhoIsMyNeighburs( [[maybe_unused]] Size_t2 position ) {
    return std::vector< Size_t2 >(0);
}

void GridAdapter::DrawGrid() {

}

void GridAdapter::Input( [[maybe_unused]] INPUT_ACTION inputAction , [[maybe_unused]]  Vector2 position ) {
    
}