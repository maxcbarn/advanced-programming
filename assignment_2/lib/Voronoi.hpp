#ifndef VORONOI_HPP
#define VORONOI_HPP

#include <vector>
#include <utility>
#include <tuple>
#include <cmath>
#include <algorithm>
#include "../lib/raylib.h"
#include "../lib/Sides.hpp"
#include "../lib/Constrains.hpp"
#include "../lib/Line.hpp"


class Voronoi
{
private:
    std::vector< Vector2 > points;
    Sides * sides;
    Constrains * constrains;
    std::deque< Vector2 > initialBox;

    void AddVertexToSite( std::deque< std::pair< Vertex * , Vertex* > > & site , std::pair< Vertex * , Vertex * > edge );
    Line PerpendicularBisector( Vector2 point1 , Vector2 point2 );
    Line LineEquation( Vector2 point1 , Vector2 point2 );
    Vector2 LineIntersectsEdge( Line linePerpBisector, Vector2 startVertex, Vector2 endVertex);
    bool IsPointInPolygon( Vector2 point , std::deque< Vector2 > polygon );
    float DistancePointToPoint( Vector2 point1 , Vector2 point2 );
public:
    Voronoi( std::vector< Vector2 > points , Sides *sides , Constrains * constrains );
    std::deque< std::deque< Vector2 > > Compute(); 
    ~Voronoi();
};


#endif // VORONOI_HPP