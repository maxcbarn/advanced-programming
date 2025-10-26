#ifndef EDGES_HPP
#define EDGES_HPP

#include "../lib/raylib.hpp"
#include "../lib/Settings.hpp"
#include <cmath>
#include <vector>
#include <tuple>

class Edges
{
private:
    std::vector< std::pair< Vector2 , Vector2 > > edges;
public:
    Edges();
    ~Edges();
    void AddEdge( Vector2 start , Vector2 end );
    void RemoveEdge( Vector2 position );
    size_t SearchEdge( Vector2 position );
    void InputAction( MouseButton mouseButton );
    void Draw();
};

#endif