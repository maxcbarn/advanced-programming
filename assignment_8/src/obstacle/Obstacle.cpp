#include "obstacle/Obstacle.hpp"
#include "grid/GridAdapterFactory.hpp"
#include "grid/GridAdapter.hpp"

Obstacle::Obstacle( Size_t2 position ) : Cell( position ) {
    this->color = BLACK;
    this->cost = INT_MAX;
}

Obstacle::~Obstacle() {

}

size_t Obstacle::GetCost() {
    return cost;
}

void Obstacle::Draw() {
    GridAdapterFactory * gridAdapterFactory = GridAdapterFactory::GetGridAdapterFactory();
    GridAdapter * gridAdapter = gridAdapterFactory->GetAdapter();
    gridAdapter->FillCell( color , position );
    delete gridAdapter;
}