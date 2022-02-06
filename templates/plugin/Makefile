# Properties

NAME				:= ../../server/plugins/$(notdir $(CURDIR))

# Commands

override CC		:= clang++
override CPPFLAGS	:= -std=c++98 -Wall -Wextra -Werror

# Sources

override SRCS		:=							\
				main.cpp						\

override HEADERS	:=							\
				myplugin.hpp					\

override HEADERS	:= $(addprefix includes/,$(HEADERS))

override OBJS		:= $(addprefix build/, $(SRCS:.cpp=.o))

override OBJDIRS	:= $(sort $(dir $(NAME) $(OBJS)))

# Rules

all:		$(NAME)

build/%.o:	src/%.cpp $(HEADERS)
			$(CC) $(CPPFLAGS) -c $< -o $@ -Iincludes

$(OBJS):	| $(OBJDIRS)

$(OBJDIRS):
			mkdir -p $@

$(NAME):	$(OBJS)
			$(CC) $(CPPFLAGS) -I ../../includes -I ../../includes/modules -fPIC --shared -Lserver -lirc -o $(NAME).so $(OBJS)

clean:
			rm -r obj

re:			fclean all

.PHONY:		all clean fclean re
