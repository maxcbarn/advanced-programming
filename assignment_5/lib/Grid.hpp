#ifndef GRID_HPP
#define GRID_HPP

#include "../lib/raylib.hpp"
#include "../lib/Points.hpp"
#include "../lib/Edges.hpp"
#include "../lib/Settings.hpp"
#include <vector>

class Grid
{
private:
    std::vector< std::vector< CELL_STATUS > > cells;
    size_t rows, columns;
public:
    Grid( size_t rows, size_t columns );
    ~Grid();
    CELL_STATUS GetCellStatus( size_t row , size_t column );
    void SetCellStatus( size_t row , size_t column , CELL_STATUS cellStatus );
};




#endif