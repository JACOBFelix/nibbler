#ifndef EXEPTION_HPP
# define EXEPTION_HPP

# include <exception>
# include <string>

class	CoreExeption : public std::exception
{
protected:
  std::string _msg;
  std::string _type;
public:
  CoreExeption(std::string const &msg);
  ~CoreExeption() throw();
  const char *what() const throw();
};

class	DLLExeption : public CoreExeption 
{
public:
  DLLExeption(std::string const &msg);
};

class	GUIExeption : public CoreExeption
{
public:
  GUIExeption(std::string const &msg);
};

class	ArgExeption : public CoreExeption
{
public:
  ArgExeption(std::string const &msg);
};
#endif // EXEPTION_HPP
