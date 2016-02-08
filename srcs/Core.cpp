#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <dlfcn.h>
#include "IGui.hpp"
#include "Core.hpp"
#include "Exeption.hpp"
#include <unistd.h>

Core::Core(int x, int y)
{
  if (x < 10 || y < 10 || x > 100 || y > 100)
    throw ArgExeption(std::string("Invalid size need a X size > 10 and a Y size > 10"));
  std::pair<int, int>	first = std::make_pair(x / 2, y / 2);
  std::pair<int, int>	two = std::make_pair(x / 2 + 1, y / 2);
  std::pair<int, int>	third = std::make_pair(x / 2 + 2, y / 2);
  std::pair<int, int>	fourth = std::make_pair(x / 2 + 3, y / 2);
  std::pair<int, int>	last = std::make_pair(x / 2 + 4, y / 2);

  _snake.push_front(first);
  _snake.push_front(two);
  _snake.push_front(third);
  _snake.push_front(fourth);
  _snake.push_front(last);
  _x = x;
  _y = y;
  _dir = LOW;
  _score = 0;
}

Core::~Core()
{
  std::cout << "You score is " << _score << std::endl;
  while (!_snake.empty())
    _snake.pop_back();
}

const std::deque<std::pair<int, int> >	&Core::getSnake() const
{
  return _snake;
}

void					Core::pop_tail()
{
  _snake.pop_back();
}

const std::pair<int, int>	        &Core::getFood() const
{
  return _food;
}

bool					Core::food_is_eat() const
{
  if (_food == _snake[0])
    return true;
  return false;
}

int					Core::get_direction() const
{
  return _dir;
}

bool					Core::is_loose() const
{
  std::pair<int, int> front = _snake.front();
  if (front.first == 0 || front.first == _x - 1 ||
      front.second == 0 || front.second == _y - 1)
    return true;
  std::deque<std::pair<int, int> >::const_iterator iter = _snake.begin();
  *iter++;
  while (iter != _snake.end() - 1)
    {
      if ((*iter).first == front.first && (*iter).second == front.second)
	return true;
      *iter++;
    }
  return false;
}

void					Core::generat_food()
{
  while (((_food.first = (rand() + 1) % _x) == 0) || _food.first == _x - 1);
  while (((_food.second = (rand() + 1) % _y) == 0) || _food.second == _y - 1);
  for (std::deque<std::pair<int, int> >::const_iterator iter = _snake.begin(); iter != _snake.end(); *iter++)
    if ((_food.first == (*iter).first && _food.second == (*iter).second) ||
	_food.first == 0 || _food.first == _x - 1 || _food.second == 0 || _food.second == _y - 1)
      {
	while (((_food.first = (rand() + 1) % _x) == 0) || _food.first == _x - 1);
	while (((_food.second = (rand() + 1) % _y) == 0) || _food.second == _y - 1);
	iter = _snake.begin();
	continue ;
      };
  _score += 10;
}

void					Core::move()
{
  std::pair<int, int> elem = _snake.front();
  switch (_dir)
    {
    case HIGH:
      _snake.push_front(std::make_pair(elem.first, elem.second - 1));
      break ;
    case LOW:
      _snake.push_front(std::make_pair(elem.first, elem.second + 1));
      break;
    case LEFT:
      _snake.push_front(std::make_pair(elem.first - 1, elem.second));
      break ;
    case RIGHT:
      _snake.push_front(std::make_pair(elem.first + 1, elem.second));
      break ;
    }
}

void					Core::change_dir(int key)
{
  switch (key)
    {
    case 1:
      _dir = (_dir + 3) % 4;
      break ;
    case 2:
      _dir = (_dir + 1) % 4;
      break ;
    }
}
