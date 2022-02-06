# Properties

NAME				:= ../../server/plugins/$(notdir $(CURDIR))

# Commands

override CC			:= clang++
override CPPFLAGS	:= -std=c++98 -Wall -Wextra -Werror

# Sources

override SRCS		:=							\
				main.cpp						\

override HEADERS	:=							\
				myplugin.hpp					\

override HEADERS	:= $(addprefix includes/,$(HEADERS))

override OBJS		:= $(addprefix build/, $(SRCS:.cpp=.o))

override OBJDIRS	:= $(sort $(dir $(NAME) $(OBJS)))

override INCLUDES	:= -I../../includes -I../../includes/modules

override LDFLAGS	:= -fPIC

# Rules

all:		$(NAME)

build/%.o:	src/%.cpp $(HEADERS)
			$(CC) $(CPPFLAGS) $(INCLUDES) -c $< -o $@ -Iincludes

$(OBJS):	| $(OBJDIRS)

$(OBJDIRS):
			mkdir -p $@

$(NAME):	$(OBJS)
			$(CC) $(CPPFLAGS) $(LDFLAGS) --shared -Lserver -lirc -o $(NAME).so $(OBJS)

clean:
			rm -rf build

re:			fclean all

.PHONY:		all clean fclean re
