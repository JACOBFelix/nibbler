#ifndef SFML_HPP_
# define SFML_HPP_

#include "IGui.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

# define	WIN_X 800
# define	WIN_Y 800

class	Sfml : public IGui
{
private:
  Sfml(const Sfml&);
  Sfml &operator=(const Sfml&);
  int			_weight;
  int			_height;
  int			_sqsize;
  sf::RenderWindow	*_win;
  sf::Clock		_clock;
  sf::SoundBuffer	_buffer[2];
  sf::Sound		_sound[2];
  sf::Image		_img[3];
  sf::Sprite		_sprite[3];
  sf::Music		_music;
  void	aff_elem(const std::deque<std::pair<int, int > > &,
			 const std::pair<int, int > &);
  void	aff_snake(const std::deque<std::pair<int, int > > &);
  void	aff_map();

public:
  Sfml(int, int);
  virtual ~Sfml();
  int	getKey();
  void	display(const std::deque<std::pair<int, int> > &,
			const std::pair<int, int> &);
  void	play_sound(int track);
};

#endif /* !SFML_HPP_ */
