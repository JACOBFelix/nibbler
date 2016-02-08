#ifndef CURSEGUI_HPP
# define CURSEGUI_HPP

#include <curses.h>
#include "IGui.hpp"

# define SNAKE		5
# define BACKGROUND	4
# define FOOD		3
# define WALL		2
# define HEAD		1

class CurseGui : public IGui
{
private:
  WINDOW	*win;
  int		_x;
  int		_y;
public:
  CurseGui(int, int);
  ~CurseGui();
  int	getKey();
  void	display(const std::deque<std::pair<int, int> > &, const std::pair<int, int> &);
  void	play_sound(int);
};

#endif // CURSEGUI_HPP
