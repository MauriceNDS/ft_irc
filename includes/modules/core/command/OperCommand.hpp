#ifndef FT_IRC_CORE_OPER_COMMAND
#define FT_IRC_CORE_OPER_COMMAND

#include "ft_irc.hpp"

#include "api/command/CommandExecutor.hpp"

class OperCommand : public CommandExecutor {

	void execute(const Command& cmd, CommandSender& sender);
};

#endif /* FT_IRC_CORE_OPER_COMMAND */
