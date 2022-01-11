#ifndef FT_IRC_CORE_QUIT_COMMAND
#define FT_IRC_CORE_QUIT_COMMAND

#include "ft_irc.hpp"

#include "api/User.hpp"
#include "api/command/CommandExecutor.hpp"

#include "server/Response.hpp"

class QuitCommand : public CommandExecutor {

	Response execute(const Command& cmd, User *sender) {
    
		return NONE;
	}
};

#endif /* FT_IRC_CORE_QUIT_COMMAND */
