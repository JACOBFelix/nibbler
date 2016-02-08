#ifndef DLL_HPP
# define DLL_HPP

class	DLL
{
private:
  void		*_lib;
public:
  DLL(const char * const lib_name);
  void		*getLib() const;
  void		*getSymbole(const char *const) const;
  ~DLL();
};
#endif // DLL_HPP
