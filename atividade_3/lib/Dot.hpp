#ifndef DOT_HPP
#define DOT_HPP

#include "../lib/raylib.h"
#include "../lib/Constrains.hpp"

class Dot
{
protected:
    Vector2 position;
    Constrains * constrains;
    Color color;
public:
    Dot( Vector2 position , Constrains * constrains , Color color );
    ~Dot();
    void ChangeColor( Color color );
    void Move( Vector2 position );
    Vector2 GetPosition();
};

#endif
