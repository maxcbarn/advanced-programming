#ifndef PATHFINDINGFACTORY_HPP
#define PATHFINDINGFACTORY_HPP

#include "../../lib/raylib.hpp"
#include "../../lib/algorithm/PathFinding.hpp"
#include "../../lib/algorithm/Dijkstra.hpp"
#include "../../lib/Settings.hpp"
#include <tuple> 
#include <vector>

class PathFindingFactory
{
private:
    
public:
    PathFindingFactory();
    PathFinding * Create( PATH_TYPE pathType );
    ~PathFindingFactory();
};






#endif