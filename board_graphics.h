#ifndef __BOARDGRAPHICS_H__
#define __BOARDGRAPHICS_H__
#include <X11/Xlib.h>
#include <iostream>
#include <string>
#include "window.h"
#include "board.h"
#include <map>
#include <utility>

class BoardGraphics {
    const int IMPROVEMENT_OFFSET = 10;
    const int NUM_SQUARES = 40;
    const int NAME_OFFSET = 3;
    const int PLAYER_OFFSET = 50;
    const int FONT_OFFSET = 10;
    const int width = 660;
    const int height = 660;
    Xwindow w;
    std::map<std::string, Colour> block_to_colour;
    const int tile_height = 60;
    const int tile_width = 60;
    Board *b;
    std::pair<int, int> indexToCoords(int index) const;

    public: 
    BoardGraphics();
    ~BoardGraphics();
    void drawTiles(Board& b);
    void printImprovements(Board &b);
    friend std::ostream &operator<<(std::ostream &out, BoardGraphics &bg);   
    void setBoard(Board* board); 
};

std::ostream &operator<<(std::ostream &out, BoardGraphics &bg);

#endif
