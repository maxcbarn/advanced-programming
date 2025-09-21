#ifndef GAME_HPP
#define GAME_HPP

#include "../lib/Point.hpp"
#include "../lib/raylib.h"
#include "../lib/Points.hpp"
#include "../lib/Constrains.hpp"
#include "../lib/Sides.hpp"
#include <memory>
#include <iostream>
#include <queue>

class Game
{
private:
    int fps, height, width;
    bool running;
    Points * points;
    Sides * sides;
    Constrains * constrains;
    Color selectedColor;

    void SetupGame();
    void DrawMenu();
    void Input();
public:
    Game( int fps, int heght ,  int width );
    void Run();
    ~Game();
};

#endif
