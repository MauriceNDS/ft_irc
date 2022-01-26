#ifndef FT_IRC_API_COMMAND_EXECUTOR
#define FT_IRC_API_COMMAND_EXECUTOR

#include "ft_irc.hpp"

#include "api/ResponseTypes.hpp"

#include "api/CommandSender.hpp"
#include "api/command/Command.hpp"

class CommandExecutor {
public:
	virtual void execute(const Command& cmd, CommandSender& sender) = 0;

	virtual ~CommandExecutor() = 0;
};

#endif /* FT_IRC_API_COMMAND_EXECUTOR */
