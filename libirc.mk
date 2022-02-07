# Properties

NAME				:= server/libirc.so

# Commands

override CC			:= clang++
override CPPFLAGS	:= -std=c++98 -Wall -Wextra -Werror
override DEPFLAGS	 = -MT $@ -MMD -MF tmp/$*.d

ifeq ($(shell uname),Darwin)
override LDFLAGS	:= -Wl,-install_name,@rpath/libirc.so -fPIC
else
override LDFLAGS	:= -fPIC
endif

# Sources

override SRCS		:=													\
				modules/api/Client.cpp									\
				modules/api/Connection.cpp								\
				modules/api/command/CommandElement.cpp					\
				modules/api/command/CommandExecutor.cpp					\
				modules/api/command/CommandManager.cpp					\
				modules/api/command/CommandSpec.cpp						\
				modules/api/command/response/ResponseSpec.cpp			\
				modules/core/Irc.cpp									\
				modules/server/Server.cpp								\

override OBJS		:= $(addprefix build/, $(SRCS:.cpp=.o))

override DEPS		:= $(addprefix tmp/, $(SRCS:.cpp=.d))

override DIRS		:= $(sort $(dir $(NAME) $(OBJS) $(DEPS)))

override INCLUDES	:= -Iincludes -Iincludes/modules

# Rules

all:		$(NAME)

$(OBJS):	| $(DIRS)

$(DIRS):
			mkdir -p $@

$(DEPS):

-include $(DEPS)

build/%.o:	%.cpp tmp/%.d
			$(CC) $(CPPFLAGS) $(DEPFLAGS) $(INCLUDES) -c $< -o $@ -Iincludes

$(NAME):	$(OBJS)
			$(CC) $(CPPFLAGS) $(LDFLAGS) --shared -o $(NAME) $(OBJS)

.PHONY:		all
