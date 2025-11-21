#ifndef GRIDADPTER_HPP
#define GRIDADPTER_HPP

#include "raylib.h"
#include "Settings.hpp"
#include "Cell.hpp"
#include <vector>


class GridAdapter
{
protected:
    size_t rows, columns;
    Vector4 windowsSize;
    
public:
    GridAdapter( size_t rows , size_t columns , Vector4 windowSize );
    virtual ~GridAdapter();
    virtual Vector2 GetCentroidOfCell( Size_t2 position );
    virtual float GetRadiusOfCell();
    virtual std::vector< Size_t2 > WhoIsMyNeighburs( Size_t2 position );
    virtual void DrawGrid();
    virtual void Input( INPUT_ACTION inputAction , Vector2 position );
};

#endif