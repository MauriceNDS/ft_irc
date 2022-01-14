#ifndef FT_IRC_CORE_USER_COMMAND
#define FT_IRC_CORE_USER_COMMAND

#include "ft_irc.hpp"

#include "api/User.hpp"
#include "api/command/CommandExecutor.hpp"

#include "server/Response.hpp"

class UserCommand : public CommandExecutor {

	Response execute(const Command& cmd, Client& sender) {
		User& user = dynamic_cast<User&>(sender);

		if (!(user.getUserName().empty()))
			return ERR_ALREADYREGISTRED;

		user.setUserName(cmd.getArg<string>("username"));
		user.setRealName(cmd.getArg<string>("realname"));
		return RPL_NONE;
	}
};

#endif /* FT_IRC_CORE_USER_COMMAND */
