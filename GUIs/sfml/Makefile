SRC	=	Sfml.cpp \
		../../CoreExeption.cpp

OBJ	=	$(SRC:.cpp=.o)

CC	=	g++

RM	=	rm -f

NAME	=	sfmllib.so

CPPFLAGS +=	-g3 -fPIC

LDFLAGS +=  -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -I ../../Includes

all:		$(NAME)

$(NAME):	$(OBJ)
		$(CC) $(OBJ) -o $(NAME) -shared -fPIC $(LDFLAGS)

clean:
		$(RM) $(OBJ)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:		re fclean clean all
