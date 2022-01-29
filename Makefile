CC = clang++

# CFLAGS = -Wall -Wextra -Werror -std=c++98
CFLAGS = -Wall -Wextra -std=c++98

HEADER =	# Headers needed

SRCS =		main.cpp # Source files needed

OBJS = $(SRCS:.cpp=.o)

NAME = ircserv

RM = rm -rf

all:    $(NAME)

$(NAME):
		clang++ $(CFLAGS) -I includes -I includes/modules -o server/plugins/test.so --shared `find plugins/test -name "*.cpp"`
		clang++ $(CFLAGS) -I includes -I includes/modules -o server/$(NAME) -Wl,-rpath -Wl,"`pwd`/server" `find . -name "*.cpp"`

%.o: %.cpp $(HEADER)
		$(CC) $(CFLAGS) -c $<  -o $@

clean:
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
