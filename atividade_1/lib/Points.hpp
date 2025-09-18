#ifndef POINTS_HPP
#define POINTS_HPP

#include "../lib/Point.hpp"
#include <vector>
#include <memory>
#include <deque>


class Points
{
private:
    std::deque< std::unique_ptr<Point> >points;
public:
    Points();
    ~Points();
    void CreatePoint( float x , float y , Constrains * constrains , Color color , int radius , float xVelocity , float yVelocity );
    Point * Search();
    void Draw();
};

#endif
