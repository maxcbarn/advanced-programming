#ifndef DIJKSTRA_HPP
#define DIJKSTRA_HPP

#include "../../lib/raylib.hpp"
#include "../../lib/grid/Cell.hpp"
#include "../../lib/algorithm/PathFinding.hpp"
#include <tuple> 
#include <vector>

class Dijkstra : PathFinding
{
protected:

public:
    Dijkstra();
    std::vector< size_t > FindPath( std::pair< size_t , size_t> start , std::pair< size_t , size_t> end , std::vector< std::vector< Cell * > > grid ) override ;
};

#endif