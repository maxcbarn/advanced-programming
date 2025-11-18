#ifndef PATHFINDING_HPP
#define PATHFINDING_HPP

#include "../../lib/raylib.hpp"
#include "../../lib/grid/Cell.hpp"
#include <tuple> 
#include <vector>

class PathFinding
{
protected:

public:
    PathFinding( );
    virtual ~PathFinding();
    virtual std::vector< size_t > FindPath( std::pair< size_t , size_t> start , std::pair< size_t , size_t> end , std::vector< std::vector< Cell * > > grid ) = 0;
};



#endif