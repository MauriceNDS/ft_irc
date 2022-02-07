CC = clang++

CFLAGS = -Wall -Wextra -Werror -std=c++98

HEADER =	# Headers needed

SRCS =		main.cpp # Source files needed

OBJS = $(SRCS:.cpp=.o)

MAIN = ircserv # executable file name

RM = rm -rf

all:    $(MAIN)

$(MAIN):
		clang++ -Wall -Wextra -std=c++98 -fsanitize=address -I includes -I includes/modules `find . -name "*.cpp"`

%.o: %.cpp $(HEADER)
		$(CC) $(CFLAGS) -c $<  -o $@

clean:
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(MAIN)

re: fclean all

.PHONY: all clean fclean re
