#ifndef SNAKE_HPP_
# define SNAKE_HPP_

# include <utility>
# include <deque>
# include "Game.hpp"

# define UP	0
# define RIGHT	1
# define DOWN	2
# define LEFT	3

# define ALIVE	0
# define DEAD	1

class	Snake
{
public:
  Snake();
  Snake(Snake const&);
  Snake& operator=(Snake const&);
  ~Snake();

public:
  std::deque< std::pair<int, int> >	getPos() const;
  std::pair<int, int>			getPosHead() const;
  std::pair<int, int>			getPosTail() const;
  int					getScore() const;
  int					getDirection() const;
  std::pair<int, int>			getNextMove() const;

  void					setScore(int);
  void					turnRight();
  void					turnLeft();
  int					moveForward(std::pair<int, int>);
  void					eatFood();
  void					popTail();
  void					pushHead(std::pair<int, int>);

private:
  std::deque< std::pair<int, int> >	_pos;
  int					_score;
  int					_direction;
};

#endif
