#ifndef FT_IRC_API_COMMAND_EXECUTOR
#define FT_IRC_API_COMMAND_EXECUTOR

#include "ft_irc.hpp"

#include "server/Response.hpp"

#include "api/User.hpp"
#include "api/command/Command.hpp"

class CommandExecutor {
public:
	virtual Response execute(const Command& cmd, User& sender) = 0;

	virtual ~CommandExecutor() {}
};

#endif /* FT_IRC_API_COMMAND_EXECUTOR */
