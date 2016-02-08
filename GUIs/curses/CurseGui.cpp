#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include "Exeption.hpp"
#include "CurseGui.hpp"

CurseGui::CurseGui(int x, int y)
{
if ((win = initscr()) == NULL || nocbreak() == ERR || noecho() == ERR ||
      keypad(stdscr, TRUE) == ERR || (win = newwin(x, y, 0, 0)) == NULL)
  throw GUIExeption(std::string("Error during init the curses library"));
  start_color();
  curs_set(0);

  if (init_pair(HEAD, COLOR_RED, COLOR_CYAN) == ERR || init_pair(WALL, COLOR_BLUE, COLOR_YELLOW) == ERR
      || init_pair(FOOD, COLOR_MAGENTA, COLOR_GREEN) == ERR || init_pair(BACKGROUND, COLOR_BLACK, COLOR_BLACK) == ERR || init_pair(SNAKE, COLOR_GREEN, COLOR_RED) == ERR)
  throw GUIExeption(std::string("Error during init the curses library"));
  _x = x;
  _y = y;
  wrefresh(win);
  int line = -1;
  while (++line < _y)
    {
      int col = -1;
      while (++col < _x)
	{
	  if (line == 0 || line == _y - 1)
	    {
	      wmove(win, col, line);
	      waddch(win, '|' | COLOR_PAIR(WALL));
	    }
	  else if (col == 0 || col == _x - 1)
	    {
	      wmove(win, col, line);
	      waddch(win, '-' | COLOR_PAIR(WALL));
	    }
	}
    }
  wrefresh(win);
}

CurseGui::~CurseGui()
{
delwin(this->win);
endwin();
echo();
}
int CurseGui::getKey()
{

wtimeout(win, 100);
int i =wgetch(win);
 if (i == 27)
   {
     i = wgetch(win);
     if (i == -1)
       return 3;
     if (i == 91)
       {
	 i = wgetch(win);
	 if (i == 'C')
	   return 1;
	 if (i == 'D')
	   return 2;
       }
   }
 return 0;
}

void	CurseGui::display(const std::deque<std::pair<int, int> > &snake,
			  const std::pair<int, int> &food)
{
  wmove(win, food.first, food.second);
  waddch(win, ' ' | COLOR_PAIR(FOOD));
  wrefresh(win);
  std::deque<std::pair<int, int> >::const_iterator iter = snake.begin();
  wmove(win, (*iter).first, (*iter).second);
  waddch(win, 'o' | COLOR_PAIR(HEAD));
  *iter++;
  while (iter != snake.end() - 1)
    {
      wmove(win, (*iter).first, (*iter).second);
      waddch(win, ' ' | COLOR_PAIR(SNAKE));
      *iter++;
    }
  wmove(win, (*iter).first, (*iter).second);
  waddch(win, ' ' | COLOR_PAIR(BACKGROUND));
  wrefresh(win);
}

void	CurseGui::play_sound(int track)
{
  beep();
  beep();
  beep();
  beep();
  beep();  (void)track;
}

extern "C"

IGui	*entry_point(int x, int y)
{
  return new CurseGui(x, y);
}
