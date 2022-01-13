#ifndef FT_IRC_CORE_USER_COMMAND
#define FT_IRC_CORE_USER_COMMAND

#include "ft_irc.hpp"

#include "api/User.hpp"
#include "api/command/CommandExecutor.hpp"

#include "server/Response.hpp"

class UserCommand : public CommandExecutor {

	Response execute(const Command& cmd, Client& sender) {
		(void)sender;
		std::cout << "'" << cmd.getArg<string>("username") << "'" << std::endl;
		std::cout << "'" << cmd.getArg<string>("realname") << "'" << std::endl;
		return RPL_NONE;
	}
};

#endif /* FT_IRC_CORE_USER_COMMAND */
