#ifndef VERTEX_HPP
#define VERTEX_HPP

#include "../lib/raylib.h"
#include "../lib/Dot.hpp"
#include <deque>

class Vertex : public Dot
{
private:
    int width;
    std::deque< Vertex * > nextVertex;

public:
    Vertex( Vector2 position , Constrains * Constrains , int width , Color color );
    ~Vertex();
    std::deque< Vertex * > GetNextVertex();
    int GetWidth();
    void Draw();
    void AddEndVertex( Vertex * vertex );
    void RemoveEndVertex( Vertex * Vertex );
    bool IsEndVertex( Vertex * vertex );
};

#endif
