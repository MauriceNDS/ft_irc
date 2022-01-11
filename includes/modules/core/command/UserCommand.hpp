#ifndef FT_IRC_CORE_USER_COMMAND
#define FT_IRC_CORE_USER_COMMAND

#include "ft_irc.hpp"

#include "api/User.hpp"
#include "server/Response.hpp"
#include "api/command/CommandExecutor.hpp"

class UserCommand : public CommandExecutor {

	Response execute(const Command& cmd, User& sender) {

		sender.setUserName(cmd.getArg<string>("user"));
		sender.setHostName(cmd.getArg<string>("host"));
		sender.setServerName(cmd.getArg<string>("server"));
		sender.setRealName(cmd.getArg<string>("real"));

		return NONE;
	}
};

#endif /* FT_IRC_CORE_USER_COMMAND */
