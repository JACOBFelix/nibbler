#ifndef XGUI_HPP
# define XGUI_HPP

#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/Xatom.h>
#include <X11/keysym.h>
#include <string>
#include "IGui.hpp"

class	XGui : public IGui
{
private:
  XGui(const XGui&);
  XGui &operator=(const XGui&);
  Window	win;
  Display	*dis;
  int		_x;
  int		_y;
  Colormap	colormap;
  GC		blue_gc;
  GC		green_gc;
  GC		red_gc;
  GC		black_gc;
  GC		white_gc;
  XColor	green_col;
  XColor	blue_col;
  XColor	red_col;
  XColor	black_col;
  XColor	white_col;
public:
  XGui(int, int);
  ~XGui();
  void	play_sound(int);
  int	getKey();
  void	display(const std::deque<std::pair<int, int> > &,
		const std::pair<int, int> &);
};
#endif //XGUI_HPP
