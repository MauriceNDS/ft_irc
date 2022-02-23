#ifndef FT_IRC_CORE_QUIT_COMMAND
#define FT_IRC_CORE_QUIT_COMMAND

#include "ft_irc.hpp"

#include "core/Irc.hpp"

#include "api/User.hpp"
#include "api/command/CommandExecutor.hpp"

#include "api/ResponseTypes.hpp"

class QuitCommand : public CommandExecutor {

	void execute(const Command& cmd, CommandSender& sender);
};

#endif /* FT_IRC_CORE_QUIT_COMMAND */
