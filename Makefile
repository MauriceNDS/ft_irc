CC = clang++
# CC = gcc-11 -lstdc++

# CFLAGS = -Wall -Wextra -Werror -std=c++98
CFLAGS = -Wall -Wextra -std=c++98 -pedantic

HEADER =	# Headers needed

SRCS =		main.cpp # Source files needed

OBJS = $(SRCS:.cpp=.o)

NAME = ircserv

RM = rm -rf

all:    $(NAME)

$(NAME):
		$(CC) $(CFLAGS) -I includes -I includes/modules -fPIC --shared -o server/libirc.so `find modules -name "*.cpp"`
		install_name_tool -id @rpath/libirc.so server/libirc.so

		$(CC) $(CFLAGS) -I includes -I includes/modules -Wl,-rpath,'@executable_path/' -ldl -Lserver -lirc -o server/$(NAME) main.cpp

		$(CC) $(CFLAGS) -I includes -I includes/modules -fPIC --shared -Lserver -lirc -o server/plugins/test.so `find plugins/test -name "*.cpp"`
		install_name_tool -id @rpath/plugins/test.so server/plugins/test.so

%.o: %.cpp $(HEADER)	
		$(CC) $(CFLAGS) -c $<  -o $@

clean:
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
