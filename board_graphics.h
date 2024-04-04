#ifndef __BOARDGRAPHICS_H__
#define __BOARDGRAPHICS_H__
#include <X11/Xlib.h>
#include <iostream>
#include <string>
#include "window.h"
#include "board.h"
#include <map>
#include <utility>

class boardGraphics {
    const int IMPROVEMENT_OFFSET = 20;
    const int NUM_SQUARES = 40;
    const int NAME_OFFSET = 3;
    std::map<std::string, Colour> block_to_colour;
    int height = 500;
    int width = 500;
    int tile_height = 45;
    int tile_width = 45;
    Xwindow w;
    std::pair<int, int> indexToCoords(int index) const;
    void drawTiles(Board& b);
};

#endif
