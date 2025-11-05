#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include "../lib/raylib.hpp"
#include "../lib/Edges.hpp"
#include "../lib/Grid.hpp"
#include "../lib/Path.hpp"
#include <tuple>
#include <cmath>
#include <algorithm>

class Interface
{
private:
    Edges * menuEdges;
    Grid * grid;
    size_t rows , columns , width , height;
    float cellRowSize , cellColumnSize; 
    std::vector< Path * > paths; 
    std::pair< size_t , size_t> start;
    bool addingPath = false;
public:
    Interface( size_t rows , size_t columns , size_t width , size_t height );
    ~Interface();
    void DrawInterface();
    void Input();
    Edges * FindPath( std::pair< size_t , size_t> start , std::pair< size_t , size_t> end );
    void CheckDeletion( size_t row , size_t column , CELL_STATUS cellStatus );
    void Recalculate();
};

#endif