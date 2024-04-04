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
    const int IMPROVEMENT_OFFSET = 20;
    const int NUM_SQUARES = 40;
    const int NAME_OFFSET = 3;
    const int PLAYER_OFFSET = 30;
    std::map<std::string, Colour> block_to_colour;
    const int height = 500;
    const int width = 500;
    const int tile_height = 45;
    const int tile_width = 45;
    Board *b;
    Xwindow w;
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
