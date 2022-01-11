#ifndef FT_IRC_CORE_NICK_COMMAND
#define FT_IRC_CORE_NICK_COMMAND

#include "ft_irc.hpp"

#include "api/User.hpp"
#include "server/Response.hpp"
#include "api/command/CommandExecutor.hpp"

class NickCommand : public CommandExecutor {

	Response execute(const Command& cmd, User& sender) {

        if (irc)
		irc.server.getUsers().pushback(new User(cmd.getArg<string>("nickname")));

		return NONE;
	}
};

#endif /* FT_IRC_CORE_NICK_COMMAND */
