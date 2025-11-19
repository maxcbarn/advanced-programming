#ifndef CELLFACTORY_HPP
#define CELLFACTORY_HPP

#include "../../lib/grid/Cell.hpp"
#include "../../lib/grid/End.hpp"
#include "../../lib/grid/Start.hpp"
#include "../../lib/grid/Obstacle.hpp"
#include "../../lib/raylib.hpp"
#include "../../lib/Settings.hpp"
#include "../../lib/grid/Empty.hpp"

class CellFactory
{
private:
    Vector2 cellSize;
public:
    CellFactory();
    ~CellFactory();
    Cell * CreateCell( CELL_STATUS cell , IntVector2 position );
};

#endif
