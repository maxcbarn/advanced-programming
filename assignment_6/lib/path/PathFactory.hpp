#ifndef PATHFACTORY_HPP
#define PATHFACTORY_HPP

#include "../../lib/raylib.hpp"
#include "../../lib/Edges.hpp"
#include "../../lib/grid/Cell.hpp"
#include "../../lib/path/Path.hpp"
#include "../../lib/path/ExactPath.hpp"
#include <tuple>
#include <cstddef>
#include <vector>


class PathFactory
{
private:
    /* data */
public:
    PathFactory();
    ~PathFactory();
    Path * Create( std::pair< size_t , size_t> start , std::pair< size_t , size_t > end );
};




#endif