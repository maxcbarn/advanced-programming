#ifndef EXACTPATH_HPP
#define EXACTPATH_HPP

#include "../../lib/raylib.hpp"
#include "../../lib/path/Path.hpp"
#include "../../lib/Edges.hpp"
#include "../../lib/algorithm/Dijkstra.hpp"
#include "../../lib/Settings.hpp"
#include <tuple>
#include <cstddef>

class ExactPath : Path
{
private:
    
public:
    ExactPath( std::pair< size_t , size_t> start , std::pair< size_t , size_t > end );
    ~ExactPath();
    void Draw( float cellRowSize , float cellColumnSize ) override;
    void Compute( std::vector< std::vector< Cell * > > grid ) override;
};


#endif