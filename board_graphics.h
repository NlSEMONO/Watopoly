#ifndef __BOARDGRAPHICS_H__
#define __BOARDGRAPHICS_H__
#include <X11/Xlib.h>
#include <iostream>
#include <string>
#include "window.h"
#include "player.h"
#include <vector>

class boardGraphics {
    int height = 500;
    int width = 500;
    int tile_height = 45;
    int tile_width = 45;
    Xwindow w;

    public:
    boardGraphics();
    void printImprovements(int tile_index);
    void printPlayers(int tile_index, std::vector<Player *> & p);
};

#endif
