# Properties

NAME				:= ../../server/plugins/$(notdir $(CURDIR)).so

# Commands

override CC			:= g++
override CPPFLAGS	:= -std=c++98 -Wall -Wextra -Werror -fPIC
override DEPFLAGS	 = -MT $@ -MMD -MF tmp/$*.d
override LDFLAGS	:= --shared

# Sources

override SRCS		:=													\
				main.cpp												\

override OBJS		:= $(addprefix build/, $(SRCS:.cpp=.o))

override DEPS		:= $(addprefix tmp/, $(SRCS:.cpp=.d))

override DIRS		:= $(sort $(dir $(NAME) $(OBJS) $(DEPS)))

override INCLUDES	:= -I../../includes -I../../includes/modules

# Rules

all:		$(NAME)

$(OBJS):	| $(DIRS)

$(DIRS):
			mkdir -p $@

$(DEPS):

-include $(DEPS)

build/%.o:	%.cpp tmp/%.d
			$(CC) $(CPPFLAGS) $(DEPFLAGS) $(INCLUDES) -c $< -o $@ -Iincludes

%.h %.hpp: ;

$(NAME):	$(OBJS)
			$(CC) $(LDFLAGS) -L../../server -lirc -o $(NAME) $(OBJS)

clean:
			rm -rf build tmp

fclean:		clean
			rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
