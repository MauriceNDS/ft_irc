#ifndef FT_IRC_CORE_NICK_COMMAND
#define FT_IRC_CORE_NICK_COMMAND

#include "ft_irc.hpp"

#include "core/Irc.hpp"

#include "api/User.hpp"
#include "api/command/CommandExecutor.hpp"

#include "server/Response.hpp"

class NickCommand : public CommandExecutor {

	Response execute(const Command& cmd, User *sender) {
		sender->setNickName(cmd.getArg<string>("nick"));
		return NONE;
	}
};

#endif /* FT_IRC_CORE_NICK_COMMAND */
