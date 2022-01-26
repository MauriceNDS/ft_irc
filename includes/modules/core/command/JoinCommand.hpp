#ifndef FT_IRC_CORE_JOIN_COMMAND
#define FT_IRC_CORE_JOIN_COMMAND

#include "ft_irc.hpp"

#include "core/Irc.hpp"

#include "api/User.hpp"
#include "api/command/CommandExecutor.hpp"

#include "server/Response.hpp"

class JoinCommand : public CommandExecutor {

	Response execute(const Command& cmd, CommandSender& sender) {
		User& user = static_cast<User&>(sender);

        vector<Channel *> channelList = cmd.getArg<vector<Channel *> >("channels");
		for (vector<Channel *>::iterator it = channelList.begin(); it != channelList.end(); it++) {
			(*it)->addUser(static_cast<User *>(&sender));
			user.send(RPL_NAMREPLY);
			user.send(RPL_TOPIC);
		}
		return RPL_NONE;
	}
};

#endif /* FT_IRC_CORE_JOIN_COMMAND */