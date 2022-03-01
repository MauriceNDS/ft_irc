#ifndef FT_IRC_CORE_MODE_COMMAND
#define FT_IRC_CORE_MODE_COMMAND

#include "ft_irc.hpp"

#include "api/command/CommandExecutor.hpp"

class ModeCommand : public CommandExecutor {
public:
	void execute(const Command& cmd, CommandSender& sender);
};

#endif /* FT_IRC_CORE_MODE_COMMAND */
