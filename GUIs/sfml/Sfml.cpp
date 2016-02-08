#include <stdexcept>
#include <iostream>
#include "Exeption.hpp"
#include "Sfml.hpp"
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/Xatom.h>
#include <X11/keysym.h>

Sfml::Sfml(int x, int y)
{
  Display	*dis;

  if ((dis = XOpenDisplay(NULL)) == NULL)
    throw GUIExeption(std::string("Error during init the sfml library"));
  _weight = x;
  _height = y;
  _sqsize = (WIN_X / x);
  _win = new sf::RenderWindow(sf::VideoMode(WIN_X, WIN_Y), "Nibbler");
  _clock = sf::Clock();

  _win->Clear();
  aff_map();

  if (!_buffer[0].LoadFromFile("./GUIs/sfml/audio_src/Sandvich.wav"))
    throw GUIExeption(std::string("Can't open Sandvich.wav file"));
  if (!_buffer[1].LoadFromFile("./GUIs/sfml/audio_src/HeavyDeath.wav"))
    throw GUIExeption(std::string("Can't open YouFailed.wav file"));
  if (!_music.OpenFromFile("./GUIs/sfml/audio_src/WhatIsLove.wav"))
    throw GUIExeption(std::string("Can't open file WhatIsLove.wav"));
  if (!_img[0].LoadFromFile("./GUIs/sfml/img_src/HeavySmiley.jpg"))
    throw GUIExeption(std::string("Can't open file HeavySmiley.jpg"));
  if (!_img[1].LoadFromFile("./GUIs/sfml/img_src/MedicSmiley.jpg"))
    throw GUIExeption(std::string("Can't open file MedicSmiley.jpg"));
  if (!_img[2].LoadFromFile("./GUIs/sfml/img_src/Sandvich.jpg"))
    throw GUIExeption(std::string("Can't open file Sandvich.jpg"));

  _img[0].CreateMaskFromColor(sf::Color::White);
  _img[1].CreateMaskFromColor(sf::Color::White);
  _img[2].CreateMaskFromColor(sf::Color::White);

  _sprite[0].SetImage(_img[0]);
  _sprite[1].SetImage(_img[1]);
  _sprite[2].SetImage(_img[2]);

  _sprite[0].SetColor(sf::Color(255,255,255,255));
  _sprite[0].Resize(_sqsize, _sqsize);

  _sprite[1].SetColor(sf::Color(255,255,255,255));
  _sprite[1].Resize(_sqsize, _sqsize);

  _sprite[2].SetColor(sf::Color(255,255,255,255));
  _sprite[2].Resize(_sqsize, _sqsize);

  _sound[0].SetBuffer(_buffer[0]);
  _sound[1].SetBuffer(_buffer[1]);
}

Sfml::~Sfml()
{
  _win->Close();
  delete _win;
}

void	Sfml::display(const std::deque<std::pair<int, int> > &snake,
		      const std::pair<int, int> &food)
{
  aff_elem(snake, food);
  _win->Display();
}

void	Sfml::aff_elem(const std::deque<std::pair<int, int> > &snake,
		       const std::pair<int, int> &food)
{
  sf::Shape rect = sf::Shape::Rectangle(0, 0, _sqsize, _sqsize, sf::Color::White);
  std::deque<std::pair<int, int> >::const_iterator it = snake.begin();

  _sprite[2].SetPosition(food.first * _sqsize, food.second * _sqsize);
  _win->Draw(_sprite[2]);

  rect.SetColor(sf::Color(127,127,127));
  rect.SetPosition((*it).first * _sqsize, (*it).second * _sqsize);
  _win->Draw(rect);
  _sprite[0].SetPosition((*it).first * _sqsize, (*it).second * _sqsize);
  _win->Draw(_sprite[0]);

  *it++;
  _sprite[1].SetPosition((*it).first * _sqsize, (*it).second * _sqsize);
  _win->Draw(_sprite[1]);

  while (it != snake.end() - 1)
    *it++;
  rect.SetColor(sf::Color(127,127,127));
  rect.SetPosition((*it).first * _sqsize, (*it).second * _sqsize);
  _win->Draw(rect);
}

void	Sfml::aff_snake(const std::deque<std::pair<int, int> > &snake)
{
  sf::Shape rect = sf::Shape::Rectangle(0, 0, _sqsize, _sqsize, sf::Color::Green);

  for (std::deque<std::pair<int, int> >::const_iterator it = snake.begin(); it != snake.end(); it++)
    {
      _sprite[1].SetPosition((*it).first * _sqsize, (*it).second * _sqsize);
      _win->Draw(_sprite[1]);
    }
}

int	Sfml::getKey()
{
  sf::Event		event;

  while (_clock.GetElapsedTime() < 0.09);
  _clock.Reset();
  while (_win->GetEvent(event))
    {
      if (event.Type == sf::Event::KeyPressed)
	{
	  if (event.Key.Code == sf::Key::Escape)
	    return (3);
	  if (event.Key.Code == sf::Key::Right)
	    return (2);
	  if (event.Key.Code == sf::Key::Left)
	    return (1);
	}
    }
  return (42);
}

void	Sfml::aff_map()
{
  sf::Shape rect = sf::Shape::Rectangle(0, 0, _sqsize, _sqsize, sf::Color::White);

    for (int y = 0; y < _height; ++y)
    {
      for (int x = 0; x < _weight; ++x)
	{
	  rect.SetPosition(x * _sqsize, y * _sqsize);
	  rect.SetColor(sf::Color::Yellow);
	  if (x != 0 && y != 0 && x != _weight - 1 && y != _height - 1)
	    rect.SetColor(sf::Color(127,127,127));
	  _win->Draw(rect);
	}
    }
  _win->Display();
}

void	Sfml::play_sound(int track)
{
  if (track > 1)
    _music.Play();
  else
    _sound[track].Play();
}

extern "C"
IGui	*entry_point(int x, int y)
{
  return new Sfml(x, y);
}
