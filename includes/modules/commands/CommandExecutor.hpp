#ifndef FT_IRC_PARSING_COMMAND_EXECUTOR
#define FT_IRC_PARSING_COMMAND_EXECUTOR

#include "ft_irc.hpp"

#include "server/Response.hpp"

#include "commands/Command.hpp"
#include "commands/CommandSender.hpp"

class CommandExecutor {
public:
	virtual Response execute(Command cmd, CommandSender sender) = 0;
	virtual ~CommandExecutor() {};
};

#endif /* FT_IRC_PARSING_COMMAND_EXECUTOR */
