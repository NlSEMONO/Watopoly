#ifndef __WINDOW_H__
#define __WINDOW_H__
#include <X11/Xlib.h>
#include <iostream>
#include <string>
#define __NUMCOL__ 11

enum Colour {White=0, Black, Red, Green, Blue, Brown, LightBlue, Pink, Orange, Yellow}; // Available colours.

class Xwindow {
  Display *d;
  Window w;
  int s, width, height;
  GC gc;
  const int numCol = 11;
  unsigned long colours[__NUMCOL__];

 public:
  Xwindow(int width=500, int height=500);  // Constructor; displays the window.
  ~Xwindow();                              // Destructor; destroys the window.

  int getWidth() const;
  int getHeight() const;

  // Draws a rectangle
  void fillRectangle(int x, int y, int width, int height, int colour=Black);

  // Draws a string
  void drawString(int x, int y, std::string msg);

};

#endif
