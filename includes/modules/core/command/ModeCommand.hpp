#ifndef FT_IRC_CORE_MODE_COMMAND
#define FT_IRC_CORE_MODE_COMMAND

#include "ft_irc.hpp"

#include "core/Irc.hpp"

#include "api/Flag.hpp"
#include "api/ResponseTypes.hpp"
#include "api/User.hpp"
#include "api/command/CommandExecutor.hpp"

#include "api/ResponseTypes.hpp"

class ModeCommand : public CommandExecutor {

	void execute(const Command& cmd, CommandSender& sender);
};

#endif /* FT_IRC_CORE_MODE_COMMAND */
