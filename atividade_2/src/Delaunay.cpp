#include "../lib/Delaunay.hpp"

Delaunay::Delaunay( Sides * sides , Constrains * constrains , std::deque< Vector2 > points , std::deque < std::deque< Vector2 > > cells ) {
    this->sides = sides;
    this->constrains = constrains;
    this->points = points;
    this->cells = cells;
}

Delaunay::~Delaunay() {
    points.clear();
}

void Delaunay::Compute() {

}