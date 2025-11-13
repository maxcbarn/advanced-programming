#ifndef EMPTY_HPP
#define EMPTY_HPP

#include "../../lib/grid/Cell.hpp"
#include "../../lib/raylib.hpp"
#include <vector>

class Empty : Cell
{
private:

public:
    Empty( Vector2 cellSize , IntVector2 position );
    ~Empty();
    using Cell::Draw;
};

#endif