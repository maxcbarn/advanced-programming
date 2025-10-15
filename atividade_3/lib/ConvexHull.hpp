#ifndef CONVEXHULL_HPP
#define CONVEXHULL_HPP

#include "../lib/raylib.h"
#include "../lib/Sides.hpp"
#include <vector>
#include <algorithm>

class ConvexHull
{
private:
    std::vector< Vector2 > points;
    Sides * sides;
public:
    ConvexHull( std::vector< Vector2 > points , Sides *sides , Constrains * Constrains);
    ~ConvexHull();
};

#endif