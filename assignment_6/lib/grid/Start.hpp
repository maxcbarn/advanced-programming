#ifndef START_HPP
#define START_HPP

#include "../../lib/grid/Cell.hpp"
#include "../../lib/raylib.hpp"
#include <vector>

class Start : Cell
{
private:

public:
    using Cell::cellSize;
    Start( IntVector2 position );
    ~Start();
    void Draw() override;
};

#endif