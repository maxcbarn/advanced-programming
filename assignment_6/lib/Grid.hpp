#ifndef GRID_HPP
#define GRID_HPP

#include "../lib/raylib.hpp"
#include "../lib/Points.hpp"
#include "../lib/Edges.hpp"
#include "../lib/Settings.hpp"
#include "../lib/grid/Cell.hpp"
#include "../lib/grid/Empty.hpp"
#include "../lib/path/Path.hpp"
#include "../lib/path/PathFactory.hpp"
#include "../lib/grid/CellFactory.hpp"
#include <vector>
#include <tuple>
#include <iostream>
#include <typeinfo>
#include <algorithm>

class Grid
{
private:
    std::vector< std::vector< Cell * > > grid;
    size_t rows, columns;
    float cellRowSize , cellColumnSize;
    std::vector< Path * > paths;
    Edges * gridDividers;
    PathFactory * pathFactory;
    CellFactory * cellFactory;
    bool addingPath = false;
    std::pair< size_t , size_t > startPath;
public:
    Grid( size_t rows, size_t columns , Vector4 windowSize );
    ~Grid();
    void Draw();
    void Input( Vector2 mousePosition , INPUT_ACTION input );
    void RecalculatePath();
    void DeleteCell( size_t row , size_t column );
};




#endif