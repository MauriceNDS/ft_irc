#ifndef FT_IRC_CORE_PING_COMMAND
#define FT_IRC_CORE_PING_COMMAND

#include "ft_irc.hpp"

#include "core/Irc.hpp"

#include "api/User.hpp"
#include "api/command/CommandExecutor.hpp"

#include "api/ResponseTypes.hpp"

class PingCommand : public CommandExecutor {

	void execute(const Command& cmd, CommandSender& sender) {
        string& server = cmd.getArg<string &>("server");
        sender.send("PONG " + server);
	}
};

#endif /* FT_IRC_CORE_PING_COMMAND */
