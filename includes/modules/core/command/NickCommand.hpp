#ifndef FT_IRC_CORE_NICK_COMMAND
#define FT_IRC_CORE_NICK_COMMAND

#include "ft_irc.hpp"

#include "api/command/CommandExecutor.hpp"

class NickCommand : public CommandExecutor {
public:
	void execute(const Command& cmd, CommandSender& sender);
};

#endif /* FT_IRC_CORE_NICK_COMMAND */
