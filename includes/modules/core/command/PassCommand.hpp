#ifndef FT_IRC_CORE_PASS_COMMAND
#define FT_IRC_CORE_PASS_COMMAND

#include "ft_irc.hpp"

#include "core/Irc.hpp"

#include "api/User.hpp"
#include "api/command/CommandExecutor.hpp"

#include "api/ResponseTypes.hpp"

class PassCommand : public CommandExecutor {

	void execute(const Command& cmd, CommandSender& sender);
};

#endif /* FT_IRC_CORE_PASS_COMMAND */
