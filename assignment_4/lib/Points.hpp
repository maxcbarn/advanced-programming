#ifndef POINTS_HPP
#define POINTS_HPP

#include "../lib/raylib.hpp"
#include "../lib/Settings.hpp"
#include <vector>
#include <cmath>

class Points
{
private:
    std::vector< Vector2 > points;
public:
    Points();
    ~Points();
    void Draw();
    void AddPoint( Vector2 point );
    size_t SearchPoint( Vector2 position );
    void RemovePoint( Vector2 position );
    void InputAction( MouseButton input );
};



#endif