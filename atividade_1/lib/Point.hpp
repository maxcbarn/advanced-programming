#ifndef POINT_HPP
#define POINT_HPP

#include "../lib/raylib.h"
#include "../lib/Dot.hpp"

class Point : public Dot
{
    private:
        Color color;
        int radius;
    public:
        Point( float x , float y , Constrains * constrains , Color color , int radius );
        ~Point();
        void Draw();
};
    
#endif 
