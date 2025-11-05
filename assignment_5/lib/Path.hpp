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
    std::pair< size_t , size_t> start , end;
    Path( std::pair< size_t , size_t> start , std::pair< size_t , size_t > end , Edges * path );
    ~Path();
    void SetPath( Edges * path );
    void Draw();
};


#endif