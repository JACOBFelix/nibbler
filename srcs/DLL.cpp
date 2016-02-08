#include <cstdlib>
#include <dlfcn.h>
#include <iostream>
#include "Exeption.hpp"
#include "DLL.hpp"

DLL::DLL(const char *const lib_name)
{
  if ((_lib = dlopen(lib_name, RTLD_LAZY)) == NULL)
    throw DLLExeption(std::string("Can't dlopen the library ") + std::string(lib_name));
}

void	*DLL::getLib() const
{
  return _lib;
}

void	*DLL::getSymbole(const char *const symbol_name) const
{
  void	*symbol;

  if ((symbol = dlsym(getLib(), symbol_name)) == NULL)
    throw DLLExeption(std::string("Can't found symbole :") + std::string(symbol_name));
  return (symbol);
}

DLL::~DLL()
{
  dlclose(_lib);
}
