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
    std::deque< Vertex * > polys;
    std::deque< Color > polysColor;
    
public:
    Sides();
    ~Sides();
    void CreateSide( Vector2 startPosition , Vector2 endPosition , Constrains * constrains , Color color , int width );
    Vertex * Search( Vector2 position );
    Vertex * SearchSide( Vector2 mousePositon );
    bool IsAPoly( Vertex * vertex );
    void AddPoly( Vertex * vertex );
    int SearchPoly( Vector2 mousePosition ); 
    void Draw();
    bool ClickInputAction( Vector2 mousePosition , Color color );
};

#endif
