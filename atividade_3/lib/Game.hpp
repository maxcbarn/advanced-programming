#ifndef GAME_HPP
#define GAME_HPP

#include "../lib/Point.hpp"
#include "../lib/raylib.h"
#include "../lib/Points.hpp"
#include "../lib/Constrains.hpp"
#include "../lib/Sides.hpp"
#include "../lib/Log.hpp"
#include "../lib/ConvexHull.hpp"
#include <memory>
#include <iostream>
#include <queue>
#include <chrono>

class Game
{
private:
    int fps, height, width;
    bool running;
    Points * points;
    Sides * sides;
    Constrains * constrains;
    Color selectedColor;
    Log * log;
    ConvexHull * convexHull;


    void SetupGame();
    void DrawMenu();
    void Input();
public:
    Game( int fps, int heght ,  int width );
    void Run();
    ~Game();
};

#endif
