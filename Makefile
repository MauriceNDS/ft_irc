# Properties

NAME				:= server/ircserv

# Commands

override CC			:= clang++
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

override DIRS		:= $(sort $(dir $(NAME) $(OBJS)))

override INCLUDES	:= -Iincludes -Iincludes/modules

# Rules

all:		dirs lib $(NAME)

dirs:		| $(DIRS)

$(DIRS):
			mkdir -p $@

tmp/%.d:	%.cpp
			@mkdir -p $(dir $@)
			@set -e; rm -f $@; \
        		$(CC) -MM $(CPPFLAGS) $(INCLUDES) $< > $@.$$$$; \
        		sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
        		rm -f $@.$$$$

build/%.o:	%.cpp
			$(CC) $(CPPFLAGS) $(DEPFLAGS) $(INCLUDES) -c $< -o $@ -Iincludes

$(NAME):	$(OBJS)
			$(CC) $(CPPFLAGS) $(LDFLAGS) -ldl -Lserver -lirc -o $(NAME) $(OBJS)

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

-include $(DEPS)
