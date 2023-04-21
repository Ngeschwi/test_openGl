SRCS	=	main.cpp \
			common/shader.cpp \
			common/texture.cpp

OBJS	=	$(SRCS:.cpp=.o)

LINK	=	-I/includes/*.hpp -I/common/*.hpp

NAME	=	OpenGlTest
CC		=	clang++
CFLAGS	=	#-Wall -Wextra -Werror #-std=c++98
LDFLAGS	=	-lglfw -lGLEW -lGL
RM		=	rm -rf

all : $(NAME)

%.o : %.cpp Makefile
	$(CC) $(CFLAGS) $(LINK) -o $@ -c $<

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $(NAME)

$(OBJS) : common/*.hpp

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : fclean $(NAME)

.PHONY:		all clean fclean re
