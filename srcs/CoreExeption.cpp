#include "Exeption.hpp"

CoreExeption::CoreExeption(std::string const & msg) : std::exception()
{
  _msg = msg;
  _type = "";
}

CoreExeption::~CoreExeption() throw()
{
}

const char	*CoreExeption::what() const throw()
{
  return ((_type + _msg).data());
}

DLLExeption::DLLExeption(std::string const &msg) : CoreExeption(msg)
{
  _msg = msg;
  _type = "";
}

GUIExeption::GUIExeption(std::string const &msg) : CoreExeption(msg)
{
  _type = "GUI Error :";
}

ArgExeption::ArgExeption(std::string const &msg) : CoreExeption(msg)
{
  _type = "";
}
