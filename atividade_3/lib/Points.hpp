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
    void CreatePoint( Vector2 position , Constrains * constrains , Color color , int radius );
    Point * Search( Vector2 mousePosition );
    void InputMouse();
    void Draw();
    bool ClickInputAction( MouseButton mouseButton , Vector2 mousePosition , Color color );
    void PopPoint( Point * point );
    int GetPointsQuantity();
    std::vector< Vector2 > GetPoints();
};

#endif
