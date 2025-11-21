#ifndef CELL_HPP
#define CELL_HPP

#include "raylib.hpp"
#include "Settings.hpp"

class Cell
    {
    protected:
        Size_t2 position;
    public:
        Cell( Size_t2 position );
        virtual ~Cell();
        virtual void Draw();
        Size_t2 GetPosition();
};


#endif