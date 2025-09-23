#ifndef SIDES_HPP
#define SIDES_HPP

#include "../lib/Vertex.hpp"
#include <vector>
#include <memory>
#include <deque>
#include <cstdlib>
#include <cmath>
#include <tuple>

class Sides
{
private:
    std::deque< std::unique_ptr< Vertex > >vertexs;
    std::deque< std::deque< Vertex * > > polys;
    Vertex * Search( Vector2 position );
    void DeleteSides( Vertex * start , Vertex * end  );
    void DeleteVertex( Vertex * vertex );
    bool CheckVertex( Vertex * vertex );
    std::tuple< Vertex * , Vertex * > SearchSide( Vector2 mousePositon );
    void CreatePolys( size_t index );
    void DeepFirstSearch(  size_t index , std::vector< bool > &bitMap , std::deque< Vertex * > &backTrack , Vertex * lastVertex );    
    size_t SearchReturnIndex( Vertex * vertex );
    void AddPoly( std::deque< Vertex * > poly );
    void CheckDeletionSidePolys( Vertex * start , Vertex * end );
    
public:
    Sides();
    ~Sides();
    void CreateSide( Vector2 startPosition , Vector2 endPosition , Constrains * constrains , Color color , int width );
    void Draw();
    bool ClickInputAction( MouseButton mouseButton , Vector2 mousePosition , Color color );
    int GetVertexQuantity();
};

#endif
