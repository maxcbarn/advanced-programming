#ifndef SIDES_HPP
#define SIDES_HPP

#include "../lib/Vertex.hpp"
#include <vector>
#include <memory>
#include <deque>


class Sides
{
private:
    std::deque< std::unique_ptr< Vertex > >vertexs;
public:
    Sides();
    ~Sides();
    void CreateSide( float xStart , float yStart , float xEnd , float yEnd  , Constrains * constrains , Color color , int width , float xStartVelocity , float yStartVelocity, float xEndVelocity , float yEndVelocity );
    Vertex * Search( float x , float y );
    void Draw();
};

#endif
