#ifndef FT_IRC_CORE_QUIT_COMMAND
#define FT_IRC_CORE_QUIT_COMMAND

#include "ft_irc.hpp"

#include "api/User.hpp"
#include "server/Response.hpp"
#include "api/command/CommandExecutor.hpp"

class QuitCommand : public CommandExecutor {

	Response execute(const Command& cmd, User& sender) {

		irc.server.killUser(sender);
        
		return NONE;
	}
};

#endif /* FT_IRC_CORE_QUIT_COMMAND */
