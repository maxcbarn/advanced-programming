#ifndef CELL_HPP
#define CELL_HPP

#include "../../lib/raylib.hpp"
#include "../../lib/Settings.hpp"

class Cell
    {
    protected:
        inline static Vector2 cellSize = Vector2{ 1.0 , 1.0 };
        IntVector2 position;
        bool blocksPath;
    public:
        Cell( Vector2 cellSize , IntVector2 position );
        virtual ~Cell() = default;
        virtual void Draw();
        bool BlocksPath();
};


#endif