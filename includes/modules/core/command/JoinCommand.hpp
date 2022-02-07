#ifndef FT_IRC_CORE_JOIN_COMMAND
#define FT_IRC_CORE_JOIN_COMMAND

#include "ft_irc.hpp"

#include "core/Irc.hpp"

#include "api/ResponseTypes.hpp"
#include "api/User.hpp"
#include "api/command/CommandExecutor.hpp"

#include "api/ResponseTypes.hpp"

class JoinCommand : public CommandExecutor {

	void execute(const Command& cmd, CommandSender& sender) {
		User& user = static_cast<User&>(sender);

		vector<Channel *>& channelList = cmd.getArg<vector<Channel *> >("channels");
		for (vector<Channel *>::iterator it = channelList.begin(); it != channelList.end(); it++) {
			(*it)->addUser(static_cast<User *>(&sender));
			user.send(ResponseTypes::RPL_NAMREPLY((*it)->getName().c_str(), sender.getName().c_str()));
			user.send(ResponseTypes::RPL_TOPIC((*it)->getName().c_str(), (*it)->getTopic().c_str()));
		}
	}
};

#endif /* FT_IRC_CORE_JOIN_COMMAND */
