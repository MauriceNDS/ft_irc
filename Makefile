#CC = clang++
CC = gcc-11 -lstdc++

# CFLAGS = -Wall -Wextra -Werror -std=c++98
CFLAGS = -Wall -Wextra -std=c++98 -pedantic

HEADER =	# Headers needed

SRCS =		main.cpp # Source files needed

OBJS = $(SRCS:.cpp=.o)

NAME = ircserv

RM = rm -rf

all:    $(NAME)

$(NAME):
# $(CC) $(CFLAGS) -I includes -I includes/modules -o server/Irc.o -c modules/core/Irc.cpp
# $(CC) $(CFLAGS) -I includes -I includes/modules -o server/Server.o -c modules/server/Server.cpp
# $(CC) $(CFLAGS) -I includes -I includes/modules -o server/Client.o -c modules/api/Client.cpp
# $(CC) $(CFLAGS) -I includes -I includes/modules -o server/Channel.o -c modules/api/Channel.cpp
# $(CC) $(CFLAGS) -I includes -I includes/modules -o server/ResponseSpec.o -c modules/api/command/response/ResponseSpec.cpp
# $(CC) $(CFLAGS) -I includes -I includes/modules -o server/CommandSpec.o -c modules/api/command/CommandSpec.cpp
# $(CC) $(CFLAGS) -I includes -I includes/modules -o server/CommandManager.o -c modules/api/command/CommandManager.cpp
# $(CC) $(CFLAGS) -I includes -I includes/modules -o server/CommandExecutor.o -c modules/api/command/CommandExecutor.cpp
# $(CC) $(CFLAGS) -I includes -I includes/modules -o server/CommandElement.o -c modules/api/command/CommandElement.cpp
# $(CC) $(CFLAGS) -I includes -I includes/modules -o server/Connection.o -c modules/api/Connection.cpp
# ar rcs server/libirc.a server/Irc.o server/Server.o server/Client.o server/Channel.o server/ResponseSpec.o server/CommandSpec.o server/CommandManager.o server/CommandExecutor.o server/CommandElement.o server/Connection.o
		$(CC) $(CFLAGS) -I includes -I includes/modules -o server/libirc.so --shared `find modules -name "*.cpp"`
		$(CC) $(CFLAGS) -I includes -I includes/modules -Lserver -lirc -o server/$(NAME) main.cpp
		$(CC) $(CFLAGS) -I includes -I includes/modules -Lserver -lirc -o server/plugins/test.so --shared `find plugins/test -name "*.cpp"`

%.o: %.cpp $(HEADER)
		$(CC) $(CFLAGS) -c $<  -o $@

clean:
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
