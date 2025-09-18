#ifndef DOT_HPP
#define DOT_HPP

#include "../lib/raylib.h"
#include "../lib/Constrains.hpp"

class Dot
{
protected:
    Vector2 position, velocity;
    Constrains * constrains;
public:
    Dot( float x , float y , Constrains * constrains );
    ~Dot();
    void Move( float x , float y );
    void SetVelocity( float x , float y ); 
    Vector2 GetPosition();
};

#endif
