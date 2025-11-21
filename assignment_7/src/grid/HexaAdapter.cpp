/* #ifndef HEXAADPTER_HPP
#define HEXAADPTER_HPP

#include "raylib.h"
#include "Settings.hpp"
#include "grid/Cell.hpp"
#include <vector>
#include "grid/GridAdapter.hpp"

class HexaAdapter : GridAdapter
{
private:
    
public:
    HexaAdapter( size_t rows , size_t columns , Vector4 windowSize );
    ~HexaAdapter();
    Vector2 GetCentroidOfCell( Size_t2 position ) override;
    float GetRadiusOfCell() override;
    std::vector< Size_t2 > HowIsMyNeighburs( Size_t2 position ) override;
};

#endif */