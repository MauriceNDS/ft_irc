# Properties

NAME				:= server/ircserv

# Commands

override CC			:= clang++
override CPPFLAGS	:= -std=c++98 -Wall -Wextra -Werror

# Sources

override SRCS		:=													\
				main.cpp												\


override HEADERS	:=													\
				ft_irc.hpp												\
				modules/api/Channel.hpp									\
				modules/api/Client.hpp									\
				modules/api/CommandSender.hpp							\
				modules/api/Connection.hpp								\
				modules/api/Plugin.hpp									\
				modules/api/ResponseTypes.hpp							\
				modules/api/User.hpp									\
				modules/api/command/Command.hpp							\
				modules/api/command/CommandElement.hpp					\
				modules/api/command/CommandExecutor.hpp					\
				modules/api/command/CommandManager.hpp					\
				modules/api/command/CommandSpec.hpp						\
				modules/api/command/GenericArguments.hpp				\
				modules/api/command/response/ResponseSpec.hpp			\
				modules/api/event/MessageEvent.hpp						\
				modules/api/exception/ArgumentNotFoundException.hpp		\
				modules/api/exception/DuplicatedCommandException.hpp	\
				modules/api/middleware/Middleware.hpp					\
				modules/api/middleware/RegisteredUserMiddleware.hpp		\
				modules/api/middleware/UserMiddleware.hpp				\
				modules/core/Irc.hpp									\
				modules/core/command/JoinCommand.hpp					\
				modules/core/command/KickCommand.hpp					\
				modules/core/command/NickCommand.hpp					\
				modules/core/command/OperCommand.hpp					\
				modules/core/command/PartCommand.hpp					\
				modules/core/command/PongCommand.hpp					\
				modules/core/command/PrivmsgCommand.hpp					\
				modules/core/command/TestCommand.hpp					\
				modules/core/command/TopicCommand.hpp					\
				modules/core/command/UserCommand.hpp					\
				modules/core/command/elements/ChannelCommandElement.hpp	\
				modules/core/command/elements/MsgToCommandElement.hpp	\
				modules/core/command/elements/UserCommandElement.hpp	\
				modules/server/Server.hpp								\


override HEADERS	:= $(addprefix includes/,$(HEADERS))

override OBJS		:= $(addprefix build/, $(SRCS:.cpp=.o))

override OBJDIRS	:= $(sort $(dir $(NAME) $(OBJS)))

override OS := $(shell uname)

ifeq ($(OS),Darwin)
override LOADER_PATH	:= @loader_path
else
override LOADER_PATH	:= $$ORIGIN
endif
override LDFLAGS	:= -Wl,-rpath,'$(LOADER_PATH)' -Wl,-rpath,'$(LOADER_PATH)/plugins'
override INCLUDES	:= -Iincludes -Iincludes/modules

# Rules

all:		lib $(NAME)

build/%.o:	%.cpp $(HEADERS)
			$(CC) $(CPPFLAGS) $(INCLUDES) -c $< -o $@ -Iincludes

$(OBJS):	| $(OBJDIRS)

$(OBJDIRS):
			mkdir -p $@

$(NAME):	$(OBJS)
			$(CC) $(CPPFLAGS) $(LDFLAGS) -ldl -Lserver -lirc -o $(NAME) $(OBJS)

ifdef N
plugin:
			bash scripts/create_plugin.bash $(N)
endif

lib:
			$(MAKE) -f libirc.mk

clean:
			rm -r obj

fclean:		clean
			rm -r server

re:			fclean all

.PHONY:		all plugin lib clean fclean re
