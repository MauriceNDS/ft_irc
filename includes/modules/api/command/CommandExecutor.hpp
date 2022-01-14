#ifndef FT_IRC_API_COMMAND_EXECUTOR
#define FT_IRC_API_COMMAND_EXECUTOR

#include "ft_irc.hpp"

#include "server/Response.hpp"

#include "api/Client.hpp"
#include "api/command/Command.hpp"

class CommandExecutor {
public:
	virtual Response execute(const Command& cmd, Client& sender) = 0;

	virtual ~CommandExecutor() = 0;
};

#endif /* FT_IRC_API_COMMAND_EXECUTOR */
