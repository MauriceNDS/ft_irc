#ifndef FT_IRC_CORE_JOIN_COMMAND
#define FT_IRC_CORE_JOIN_COMMAND

#include "ft_irc.hpp"

#include "core/Irc.hpp"

#include "api/User.hpp"
#include "api/command/CommandExecutor.hpp"

#include "server/Response.hpp"

class JoinCommand : public CommandExecutor {

	Response execute(const Command& cmd, CommandSender& sender) {

        vector<string>
		Irc::getInstance().findChannel()
		return RPL_NONE;
	}
};

#endif /* FT_IRC_CORE_JOIN_COMMAND */