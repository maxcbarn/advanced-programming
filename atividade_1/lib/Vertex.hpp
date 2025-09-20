#ifndef VERTEX_HPP
#define VERTEX_HPP

#include "../lib/raylib.h"
#include "../lib/Dot.hpp"

class Vertex : public Dot
{
private:
    int width;
    Vertex * endVertex;

public:
    Vertex( Vector2 position , Constrains * Constrains , int width , Color color );
    ~Vertex();
    Vector2 GetEndVertexPosition();
    Vertex * GetEndVertex();
    int GetWidth();
    void Draw();
    void SetEndVertex( Vertex * vertex );
};

#endif
