#ifndef SQUAREADPTER_HPP
#define SQUAREADPTER_HPP

#include "raylib.h"
#include "Settings.hpp"
#include "Cell.hpp"
#include <vector>
#include "grid/GridAdapter.hpp"
#include "grid/Grid.hpp"
#include <cmath>

class SquareAdapter : GridAdapter
{
protected:
    float rowSize, columnSize;
public:
    SquareAdapter(  size_t rows , size_t columns , Vector4 windowSize  );
    ~SquareAdapter();
    Vector2 GetCentroidOfCell( Size_t2 position ) override;
    float GetRadiusOfCell() override;
    std::vector< Size_t2 > WhoIsMyNeighburs( Size_t2 position ) override;
    void DrawGrid() override;
    void Input( INPUT_ACTION inputAction , Vector2 position ) override;
};

#endif