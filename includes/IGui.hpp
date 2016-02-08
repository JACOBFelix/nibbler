
#ifndef IGUI_HPP_
#define IGUI_HPP_

#include <deque>
#include <utility>
#include <iostream>
class		IGui
{
public:
  virtual ~IGui(){};
  virtual int		getKey() = 0;
  virtual void		display(const std::deque<std::pair<int, int> > &,
			        const std::pair<int, int> &) = 0;
  virtual void		play_sound(int) = 0;
};

// snake dans une std::deque
// juste print le premier element dans la couleur de la tete (au choix)
// print le deuxieme element de la deque dans la couleur du snake
// print le dernier element de la deque dans la couleur du background
// print la food qui est une std::pair contenu dans le Core (get_food)

#endif //
