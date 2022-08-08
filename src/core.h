#ifndef CORE_H
#define CORE_H

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int GRID_WIDTH = 20;
const int GRID_HEIGHT = 15;
const int SQUARE_SIZE = 32;
const int SCREEN_FPS = 30;
const int SCREEN_TICK_PER_FRAME = 1000 / SCREEN_FPS;

struct position
{
    unsigned int x;
    unsigned int y;
};

enum direction{
    UP, RIGHT, DOWN, LEFT
};

#endif