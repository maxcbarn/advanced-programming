#ifndef POINT_HPP
#define POINT_HPP

#include "../lib/raylib.h"
#include "../lib/Dot.hpp"
#include <vector>


class Point : public Dot
{
    private:
        int radius;
    public:
        Point( Vector2 position , Constrains * constrains , Color color , int radius );
        ~Point();
        int GetRaius();
        void Draw();
};
    
#endif 
