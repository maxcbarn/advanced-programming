#ifndef COLLISOR_HPP
#define COLLISOR_HPP

#include <cstddef>

class Collisor
{
private:
    size_t cost;
    bool isCellFill;
    float radius;
public:
    Collisor( size_t cost , bool cellFill , float radius );
    ~Collisor();
    bool IsCellFill();
    size_t GetCost();
    float GetRadius();
};



#endif