#ifndef CORE_HPP
# define CORE_HPP

# include <deque>
# include <utility>

# define HIGH	0
# define RIGHT	1
# define LOW	2
# define LEFT	3


class	Core
{
private:
  Core(const Core&);
  Core &operator=(const Core&);
public:
  Core(int, int);
  ~Core();
  const std::deque<std::pair<int, int> >	&getSnake() const;
  const std::pair<int, int>		&getFood() const;
  void					pop_food(int, int);
  void					pop_tail();
  void					generat_food();
  bool					food_is_eat() const;
  bool					is_loose() const;
  int					get_direction() const;
  void					change_dir(int);
  void					move();
private:
  std::deque<std::pair<int, int> >	_snake;
  std::pair<int, int>			_food;
  int					_score;
  int					_x;
  int					_y;
  int					_dir;
};
#endif // CORE_HPP
