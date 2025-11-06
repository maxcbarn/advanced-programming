#ifndef PATH_HPP
#define PATH_HPP

#include "../lib/raylib.hpp"
#include "../lib/Edges.hpp"
#include <tuple>
#include <cstddef>

class Path
{
private:
    Edges * path;
public:
    std::vector< size_t > pathRowsColumns;
    std::pair< size_t , size_t> start , end;
    
    Path( std::pair< size_t , size_t> start , std::pair< size_t , size_t > end , std::pair< Edges * , std::vector< size_t > > path  );
    ~Path();
    void SetPath( std::pair< Edges * , std::vector< size_t > > path );
    void Draw();
};


#endif