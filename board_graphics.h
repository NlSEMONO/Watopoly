#ifndef __BOARDGRAPHICS_H__
#define __BOARDGRAPHICS_H__
#include <X11/Xlib.h>
#include <iostream>
#include <string>
#include "window.h"

class boardGraphics {
    int height;
    int width;
    int tile_height;
    int tile_width;
    Xwindow w;
};

#endif
