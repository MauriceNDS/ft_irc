#ifndef FT_IRC_CORE_PING_COMMAND
#define FT_IRC_CORE_PING_COMMAND

#include "ft_irc.hpp"

#include "api/command/CommandExecutor.hpp"

class PingCommand : public CommandExecutor {

	void execute(const Command& cmd, CommandSender& sender);
};

#endif /* FT_IRC_CORE_PING_COMMAND */
