GXX=	g++

RM=	rm -f

SRCS=	./srcs/main.cpp \
	./srcs/DLL.cpp \
	./srcs/Core.cpp \
	./srcs/CoreExeption.cpp

OBJS=	$(SRCS:.cpp=.o)

CXXFLAGS=	-W -Wall -Wextra -Werror -I ./includes/

NAME=		nibbler

SRCSCURS=	./GUIs/curses/CurseGui.cpp \
		./srcs/CoreExeption.cpp

OBJSCURS=	$(SRCSCURS:.cpp=.o)

LIBCURS=	lib_nibbler_ncurses.so

XSRCS=		./GUIs/Xlib/XGui.cpp \
		./srcs/CoreExeption.cpp

XOBJS=		$(XSRCS:.cpp=.o)

XLIB=		lib_nibbler_xlib.so

SFMLSRCS=	./GUIs/sfml/Sfml.cpp \
		./srcs/CoreExeption.cpp

SFMLOBJS=	$(SFMLSRCS:.cpp=.o)

SFMLLIB=	lib_nibbler_sfml.so

CXXFLAGS+=	-rdynamic -fPIC

LIBXFLAGS=	 -lX11

SFMLFLAGS=	-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

all:		$(NAME) $(LIBCURS) $(XLIB) $(SFMLLIB)

$(NAME):	$(OBJS)
		$(GXX) $(OBJS) -o $(NAME) $(CXXFLAGS) -ldl

$(LIBCURS):	$(OBJSCURS)
		$(GXX) $(OBJSCURS) -o $(LIBCURS) -shared -lncurses $(CXXFLAGS)

$(XLIB):	 $(XOBJS)
		$(GXX) $(XOBJS) -o $(XLIB) -shared -rdynamic $(CXXFLAGS) $(LIBXFLAGS)

$(SFMLLIB):	$(SFMLOBJS)
		$(GXX) $(SFMLOBJS) -o $(SFMLLIB) -shared -fPIC -rdynamic $(SFMLFLAGS) -lX11
clean:
		$(RM) $(OBJS)
		$(RM) $(OBJSCURS)
		$(RM) $(XOBJS)
		$(RM) $(SFMLOBJS)
fclean:	clean
		$(RM) $(NAME)
		$(RM) $(LIBCURS)
		$(RM) $(XLIB)
		$(RM) $(SFMLLIB)

re:	fclean all

.PHONY:	all clean fclean re
