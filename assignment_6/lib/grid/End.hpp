#ifndef END_HPP
#define END_HPP

#include "../../lib/grid/Cell.hpp"
#include "../../lib/raylib.hpp"
#include <vector>

class End : Cell
{
private:

public:
    End( Vector2 cellSize , IntVector2 position );
    ~End();
    void Draw() override;
};

#endif