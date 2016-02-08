#include <cstdlib>
#include "XGui.hpp"
#include "Exeption.hpp"

extern "C"

IGui	*entry_point(int x, int y)
{
  return new XGui(x, y);
}

XGui::XGui(int x, int y)
{
  char	green[] = "#00FF00";
  char	blue[] = "#0000FF";
  char	black[] = "#000000";
  char	red[] = "#FF0000";
  char	white[] = "#FFFFFF";
  _x = x;
  _y = y;
  if ((dis = XOpenDisplay(NULL)) == NULL)
    throw GUIExeption(std::string("Error during init the curses library"));
  win = XCreateSimpleWindow(dis, RootWindow(dis, 0), 1, 1, x * 10, y * 10, 0,
			    BlackPixel(dis, 0), BlackPixel(dis, 0));
  XSelectInput(dis, win, KeyPressMask | ButtonPressMask);
  XMapWindow(dis, win);
  colormap = DefaultColormap(dis, 0);
  green_gc = XCreateGC(dis, win, 0, 0);
  XParseColor(dis, colormap, green, &green_col);
  XAllocColor(dis, colormap, &green_col);
  blue_gc = XCreateGC(dis, win, 0, 0);
  XParseColor(dis, colormap, blue, &blue_col);
  XAllocColor(dis, colormap, &blue_col);
  black_gc = XCreateGC(dis, win, 0, 0);
  XParseColor(dis, colormap, black, &black_col);
  XAllocColor(dis, colormap, &black_col);
  red_gc = XCreateGC(dis, win, 0, 0);
  XParseColor(dis, colormap, red, &red_col);
  XAllocColor(dis, colormap, &red_col);
  white_gc = XCreateGC(dis, win, 0, 0);
  XParseColor(dis, colormap, white, &white_col);
  XAllocColor(dis, colormap, &white_col);
  XSetForeground(dis, green_gc, green_col.pixel);
  for (int i = 0; i < x * 10; i += 10)
    {
      XSetForeground(dis, blue_gc, blue_col.pixel);
      XDrawRectangle(dis, win, blue_gc, 1 + i, 1, 10, 10);
      XFlush(dis);
      XSetForeground(dis, blue_gc, blue_col.pixel);
      XFlush(dis);
      XDrawRectangle(dis, win, blue_gc, 1, 1 + i, 10, 10);
      XFlush(dis);
      usleep(1);
      XDrawRectangle(dis, win, blue_gc, 1 + i, y * 10 - 10, 10, 10);
      XFlush(dis);
      XDrawRectangle(dis, win, blue_gc, x * 10 - 10, i + 1, 10, 10);
      XFlush(dis);
    }
  XFlush(dis);
}

XGui::~XGui()
{
  XUnmapWindow (dis, win);
}

int	XGui::getKey()
{
  XEvent	event;
  int nbevent = XEventsQueued(dis, QueuedAlready);
  while (nbevent-- != 0)
    {
      XNextEvent(dis, &event);
      if (event.type == KeyPress)
	{
	  int val = XLookupKeysym(&event.xkey, 0);
	  if (val == 65361)
	    return 1;
	  if (val == 65363)
	    return 2;
	  if (val == 65307)
	    return 3;
	}
    }
  return 42;
}

void	XGui::play_sound(int)
{
}

void    XGui::display(const std::deque<std::pair<int, int> > &snake,
		      const std::pair<int, int> &food)
{
  std::deque<std::pair<int, int> >::const_iterator iter = snake.begin();
  XSetForeground(dis, white_gc, white_col.pixel);
  XDrawRectangle(dis, win, white_gc, food.first * 10, food.second * 10, 10, 10);
  XFlush(dis);
  usleep(50000);
  XSetForeground(dis, red_gc, red_col.pixel);
  XDrawRectangle(dis, win, red_gc, (*iter).first * 10, (*iter).second * 10, 10, 10);
  usleep(50000);
  XFlush(dis);
  *iter++;
  while (iter != snake.end() - 1)
    {
      XSetForeground(dis, green_gc, green_col.pixel);
      XDrawRectangle(dis, win, green_gc, (*iter).first * 10, (*iter).second * 10, 10, 10);
      XFlush(dis);
      *iter++;
    }
  XSetForeground(dis, black_gc, black_col.pixel);
  XDrawRectangle(dis, win, black_gc, (*iter).first * 10, (*iter).second * 10, 10, 10);
  XFlush(dis);
}
