#include <unistd.h>
#include <ctime>
#include <iostream>
#include <cstdlib>
#include "Core.hpp"
#include "DLL.hpp"
#include "IGui.hpp"
#include "Exeption.hpp"

int	main(int ac, char **ag)
{
  try
    {
      if (ac < 4)
	throw ArgExeption(std::string("Invalid argument need [X size] [Y size] [libNAME.so]"));

      Core	core(std::atoi(ag[1]), std::atoi(ag[2]));
      DLL	dll(ag[3]);
      IGui	*(*fct)(int, int) = reinterpret_cast<IGui *(*)(int, int)>(dll.getSymbole("entry_point"));
      IGui	*gui = fct(std::atoi(ag[1]), std::atoi(ag[2]));

      std::srand(std::time(0));
      gui->play_sound(2);
      core.generat_food();
      gui->display(core.getSnake(), core.getFood());
      int i = 0;
      while (core.is_loose() == false)
	{
	  core.move();
	  if (core.food_is_eat() == true)
	    {
	      core.generat_food();
	      gui->play_sound(0);
	    }
	  else
	    core.pop_tail();
  	  gui->display(core.getSnake(), core.getFood());
	  i = gui->getKey();
  	  if (i == -1 || i == 3)
	    break ;
	  core.change_dir(i);
	}
      gui->play_sound(1);
      sleep(2);
      if (i == -1 || i == 3)
	std::cout << "Bad Guy You Gonne be fesses" << std::endl;
      else
	std::cout << "You lost" << std::endl;
      delete gui;
    }
  catch (CoreExeption const &e)
    {
      std::cerr << e.what() << std::endl;
      return (-1);
    }
  return 0;
}
