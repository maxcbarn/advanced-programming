#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include "../lib/raylib.hpp"

#define POINT_RADIUS 6
#define POINT_COLOR BLUE

#define EDGE_WIDTH 4
#define EDGE_MENU_COLOR WHITE
#define EDGE_PATH_COLOR ORANGE

#define STD_POLY_COLOR GREEN

enum CELL_STATUS {
    EMPTY,
    OBSTACLE,
    START,
    END,
};

#define EMPTY_COLOR BLACK
#define OBSTACLE_COLOR RED
#define START_COLOR GREEN
#define END_COLOR BLUE

#endif