#ifndef CELL_HPP
#define CELL_HPP

#include "../../lib/raylib.hpp"
#include "../../lib/Settings.hpp"

class Cell
    {
    protected:
        IntVector2 position;
        bool blocksPath;
    public:
        inline static Vector2 cellSize = Vector2{ 1 , 1 };
        Cell( IntVector2 position );
        virtual ~Cell() = default;
        virtual void Draw();
        bool BlocksPath();
};


#endif