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
    int height;
    int width;
    int tile_height;
    int tile_width;
    const int IMPROVEMENT_OFFSET = 20;
    const int NUM_SQUARES = 40;
    const int NAME_OFFSET = 3;
    std::map<std::string, Colour> block_to_colour;
    Xwindow w;
    std::pair<int, int> indexToCoords(int index) const;
    void drawTiles(Board& b);
};

#endif
