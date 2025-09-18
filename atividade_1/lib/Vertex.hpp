#ifndef VERTEX_HPP
#define VERTEX_HPP

#include "../lib/raylib.h"
#include "../lib/Dot.hpp"

class Vertex : public Dot
{
private:
    Color color;
    int width;
    Vertex * endVertex;

public:
    Vertex(  float x , float y , Constrains * Constrains , int width , Color color );
    ~Vertex();
    Vector2 GetEndVertexPosition();
    Vertex * GetEndVertex();
    void Draw();
    void SetEndVertex( Vertex * vertex );
};

#endif
