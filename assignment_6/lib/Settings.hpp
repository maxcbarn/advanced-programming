#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include "../lib/raylib.hpp"
#include <cstddef>

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

enum INPUT_ACTION {
    LEFT_CLICK,
    RIGHT_CLICK,
    MIDDLE_CLICK,
    BUTTON_ONE_CLICK,
    BUTTON_TWO_CLICK,
    NONE,
};

enum PATH_TYPE {
    EXACT,
};

typedef struct IntVector2 {
    size_t x;
    size_t y;
} IntVector2;

#define EMPTY_COLOR BLACK
#define OBSTACLE_COLOR RED
#define START_COLOR GREEN
#define END_COLOR BLUE

#endif