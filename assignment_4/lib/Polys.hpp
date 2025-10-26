#ifndef POLYS_HPP
#define POLYS_HPP

#include "../lib/raylib.hpp"
#include <vector>
class Polys
{
private:
    std::vector< std::vector< Vector2 > > polys;
    std::vector< Color > colors; 
public:
    Polys();
    ~Polys();
    void Draw();
    void AddPoly( std::vector< Vector2 > poly , Color color );
    size_t SearchPoly( Vector2 position );
    void RemovePoly( Vector2 position );
    void InputAction( MouseButton input );
    std::vector< std::vector< Vector2 > > GetPolys();
};


#endif