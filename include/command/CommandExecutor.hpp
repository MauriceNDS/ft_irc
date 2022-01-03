#ifndef FT_IRC_COMMAND_EXECUTOR
#define FT_IRC_COMMAND_EXECUTOR

#include "core.hpp"
#include "Response.hpp"
#include "command/Command.hpp"
#include "command/CommandSender.hpp"

class CommandExecutor {
public:
	virtual Response execute(Command cmd, CommandSender sender) = 0;
};

#endif /* FT_IRC_COMMAND_EXECUTOR */
