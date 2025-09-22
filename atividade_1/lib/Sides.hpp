#ifndef SIDES_HPP
#define SIDES_HPP

#include "../lib/Vertex.hpp"
#include <vector>
#include <memory>
#include <deque>
#include <thread>
#include <cstdlib>
#include <cmath>

class Sides
{
private:
    std::deque< std::unique_ptr< Vertex > >vertexs;
    std::deque< std::deque< Vertex * > > polys;
public:
    Sides();
    ~Sides();
    void CreateSide( Vector2 startPosition , Vector2 endPosition , Constrains * constrains , Color color , int width );
    Vertex * Search( Vector2 position );
    Vertex * SearchSide( Vector2 mousePositon );
    void Draw();
    bool ClickInputAction( MouseButton mouseButton , Vector2 mousePosition , Color color );
    void DeleteSides( Vertex * start );
    void DeleteVertex( Vertex * vertex );
    bool CheckVertex( Vertex * vertex );
    int GetVertexQuantity();
    void CreatePolys();
};

#endif
