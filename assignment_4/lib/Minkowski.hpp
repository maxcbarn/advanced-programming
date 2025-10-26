#ifndef MINKOWSKI_HPP
#define MINKOWSKI_HPP

#include "../lib/raylib.hpp"
#include <vector>
#include <algorithm>

class Minkowski
{
private:
    std::vector< std::vector< Vector2 > > polys;
    std::vector< Vector2 > robot;
public:
    Minkowski();
    void SetData(  std::vector< std::vector< Vector2 > > polys , std::vector< Vector2 > robot  );
    std::vector< std::vector< Vector2 > > Compute();
    ~Minkowski();
};

#endif