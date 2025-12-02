#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include "raylib.hpp"
#include <cstddef>

#define MENU_LINE_COLOR WHITE
#define MENU_LINE_WIDTH 4

#define END_COLOR BLUE
#define START_COLOR GREEN
#define PATH_COLOR ORANGE
#define AGENT_COLOR RED
#define PATH_WIDTH 2

enum INPUT_ACTION {
    ADD_MUD,
    ADD_WALL,
    ADD_AGENT,
    REMOVE,
    NONE,
};

enum INPUT {
    LEFT_CLICK,
    RIGHT_CLICK,
    ONE,
    TWO,
    THREE,
};

enum OBSTACLE_TYPE {
    WALL,
    MUD,
};

enum TYPE_GRID {
    SQUARE,
    HEXA,
};

typedef struct Size_t2 {
    size_t x;
    size_t y;
} IntVector2;

#endif