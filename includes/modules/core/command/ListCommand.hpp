#ifndef FT_IRC_CORE_LIST_COMMAND
#define FT_IRC_CORE_LIST_COMMAND

#include "ft_irc.hpp"

#include "api/command/CommandExecutor.hpp"

class ListCommand : public CommandExecutor {

	void execute(const Command& cmd, CommandSender& sender);
};

#endif /* FT_IRC_CORE_LIST_COMMAND */
