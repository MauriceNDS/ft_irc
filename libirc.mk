# Properties

NAME				:= server/libirc.so

# Commands

CC					:= clang++
override CPPFLAGS	:= -g3 -std=c++98 -Wall -Wextra -Werror -fPIC
override DEPFLAGS	 = -MT $@ -MMD -MF tmp/$*.d
override LDFLAGS	:= --shared

ifeq ($(shell uname),Darwin)
LDFLAGS				+= -Wl,-install_name,@rpath/libirc.so
endif

# Sources

override SRCS		:=													\
				modules/api/Client.cpp									\
				modules/api/User.cpp									\
				modules/api/Channel.cpp									\
				modules/api/Connection.cpp								\
				modules/api/Flag.cpp									\
				modules/api/Plugin.cpp									\
				modules/api/PluginLoader.cpp							\
				modules/api/command/Command.cpp							\
				modules/api/command/CommandElement.cpp					\
				modules/api/command/CommandExecutor.cpp					\
				modules/api/command/CommandManager.cpp					\
				modules/api/command/CommandSpec.cpp						\
				modules/api/command/GenericArguments.cpp				\
				modules/api/command/element/FlagsCommandElement.cpp		\
				modules/api/command/response/ResponseSpec.cpp			\
				modules/api/event/MessageEvent.cpp						\
				modules/api/exception/ArgumentNotFoundException.cpp		\
				modules/api/exception/DuplicatedCommandException.cpp	\
				modules/api/exception/NoNameProvidedException.cpp		\
				modules/api/middleware/Middleware.cpp					\
				modules/api/middleware/RegisteredUserMiddleware.cpp		\
				modules/api/middleware/UserMiddleware.cpp				\
				modules/api/middleware/ValidPassMiddleware.cpp			\
				modules/core/command/InviteCommand.cpp					\
				modules/core/command/JoinCommand.cpp					\
				modules/core/command/KickCommand.cpp					\
				modules/core/command/ListCommand.cpp					\
				modules/core/command/ModeCommand.cpp					\
				modules/core/command/NamesCommand.cpp					\
				modules/core/command/NickCommand.cpp					\
				modules/core/command/NoticeCommand.cpp					\
				modules/core/command/OperCommand.cpp					\
				modules/core/command/PartCommand.cpp					\
				modules/core/command/PassCommand.cpp					\
				modules/core/command/PingCommand.cpp					\
				modules/core/command/PrivmsgCommand.cpp					\
				modules/core/command/QuitCommand.cpp					\
				modules/core/command/TopicCommand.cpp					\
				modules/core/command/UserCommand.cpp					\
				modules/core/command/element/ChannelCommandElement.cpp	\
				modules/core/command/element/MsgToCommandElement.cpp	\
				modules/core/command/element/UserCommandElement.cpp		\
				modules/core/Irc.cpp									\
				modules/server/Server.cpp								\
				modules/api/utils.cpp									\

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

%.h %.hpp: ;

$(NAME):	$(OBJS)
			$(CC) $(LDFLAGS) -o $(NAME) $(OBJS)

.PHONY:		all
