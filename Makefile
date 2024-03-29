# Properties

NAME				:= server/ircserv

# Commands

CC					:= g++
override CPPFLAGS	:= -std=c++98 -Wall -Wextra -Werror
override DEPFLAGS	 = -MT $@ -MMD -MF tmp/$*.d

ifeq ($(shell uname),Darwin)
override LOADER_PATH	:= @loader_path
else
override LOADER_PATH	:= $$ORIGIN
endif
override LDFLAGS	:= -Wl,-rpath,'$(LOADER_PATH)' -Wl,-rpath,'$(LOADER_PATH)/plugins'

# Sources

override SRCS		:=													\
				main.cpp												\

override OBJS		:= $(addprefix build/, $(SRCS:.cpp=.o))

override DEPS		:= $(addprefix tmp/, $(SRCS:.cpp=.d))

override DIRS		:= $(sort $(dir $(NAME) $(OBJS) $(DEPS)))

override INCLUDES	:= -Iincludes -Iincludes/modules

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
			$(CC) -o $(NAME) $(OBJS) $(LDFLAGS) -Lserver -lirc

ifdef N
plugin:
			bash scripts/create_plugin.bash $(N)
endif

lib:
			$(MAKE) -f libirc.mk

clean:
			rm -rf build tmp

fclean:		clean
			rm -rf server

re:			fclean all

.PHONY:		all plugin lib clean fclean re
