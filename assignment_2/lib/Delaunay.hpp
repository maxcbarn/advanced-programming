#ifndef DELAUNAY_HPP
#define DELAUNAY_HPP

#define EDGE_WIDTH 2

#include "../lib/Sides.hpp"
#include "../lib/raylib.h"
#include <deque>

class Delaunay
{
private:
    Sides* sides;
    std::deque< Vector2 > points;
    Constrains * constrains;
    std::deque < std::deque< Vector2 > > cells;

public:
    Delaunay( Sides * sides , Constrains * constrains , std::deque< Vector2 > points , std::deque < std::deque< Vector2 > > cells );
    ~Delaunay();
    void Compute();
};

#endif