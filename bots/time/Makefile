# Properties

NAME				:= timebot

# Commands

CC					:= clang++
override CPPFLAGS	:= -std=c++98 -Wall -Wextra -Werror
override DEPFLAGS	 = -MT $@ -MMD -MF tmp/$*.d

# Sources

override SRCS		:=													\
				main.cpp												\

override OBJS		:= $(addprefix build/, $(SRCS:.cpp=.o))

override DEPS		:= $(addprefix tmp/, $(SRCS:.cpp=.d))

override DIRS		:= $(sort $(dir $(NAME) $(OBJS) $(DEPS)))

override INCLUDES	:= -I.

# Rules

all:		lib $(NAME)

$(OBJS):	| $(DIRS)

$(DIRS):
			mkdir -p $@

$(DEPS):

-include $(DEPS)

build/%.o:	%.cpp tmp/%.d
			$(CC) $(CPPFLAGS) $(DEPFLAGS) $(INCLUDES) -c $< -o $@ -Iincludes

%.h %.hpp: ;

$(NAME):	$(OBJS)
			$(CC) -o $(NAME) $(OBJS)

clean:
			rm -rf build tmp

fclean:		clean
			rm -rf server

re:			fclean all

.PHONY:		all plugin lib clean fclean re
