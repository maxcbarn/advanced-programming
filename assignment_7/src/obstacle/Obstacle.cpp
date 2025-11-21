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
    
    Vector2 centroid = gridAdapter->GetCentroidOfCell( position );
    float radius = gridAdapter->GetRadiusOfCell();
    
    Vector2 origin = Vector2{ centroid.x - radius , centroid.y - radius };
    Vector2 size = Vector2{ radius * 2 , radius * 2 };

    DrawRectangleV( origin , size , color );
}