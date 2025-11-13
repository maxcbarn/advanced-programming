#ifndef DIJKSTRA_HPP
#define DIJKSTRA_HPP

#include "../../lib/raylib.hpp"
#include "../../lib/grid/Cell.hpp"
#include <tuple> 
#include <vector>

class Dijkstra
{
private:
    std::vector< size_t > path;
public:
    Dijkstra( std::pair< size_t , size_t> start , std::pair< size_t , size_t> end , std::vector< std::vector< Cell * > > grid );
    std::vector< size_t > GetPath();
    ~Dijkstra();
};

#endif