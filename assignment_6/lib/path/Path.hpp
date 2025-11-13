#ifndef PATH_HPP
#define PATH_HPP

#include "../../lib/raylib.hpp"
#include "../../lib/Edges.hpp"
#include "../../lib/grid/Cell.hpp"
#include <tuple>
#include <cstddef>
#include <vector>

class Path
{
protected:
    std::pair< size_t , size_t> start , end;
    std::vector< size_t > pathRowsColumns;
public:
    Path( std::pair< size_t , size_t> start , std::pair< size_t , size_t > end );
    virtual ~Path() = default;
    virtual void Draw( float cellRowSize , float cellColumnSize ) = 0;
    virtual void Compute( std::vector< std::vector< Cell * > > grid ) = 0;
    std::pair< size_t , size_t> GetStart();
    std::pair< size_t , size_t> GetEnd(); 
    std::vector< size_t > GetPath();
};


#endif