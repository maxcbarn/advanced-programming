#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

#include "../../lib/grid/Cell.hpp"
#include "../../lib/raylib.hpp"
#include <vector>

class Obstacle : Cell
{
protected:
    bool blocksPath = true;
public:
    Obstacle( IntVector2 position );
    ~Obstacle();
    void Draw() override;
};

#endif