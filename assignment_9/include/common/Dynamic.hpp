#ifndef DYNAMIC_HPP
#define DYNAMIC_HPP

#include "raylib.hpp"

class Dynamic
{
private:
    Vector2 dynamicPosition;
    float velocity;
public:
    Dynamic( Vector2 dynamicPositon , float velocity );
    ~Dynamic();
    float GetVelocity();
    void SetDynamicPosition( Vector2 position );
    Vector2 GetDynamicPosition();
};

#endif
