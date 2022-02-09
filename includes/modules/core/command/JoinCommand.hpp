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
		string from = user.getNickName() + "!" + user.getUserName() + "@" + Irc::getInstance().getServer().getHost();

		vector<Channel *>& channelList = cmd.getArg<vector<Channel *> >("channels");
		for (vector<Channel *>::iterator it = channelList.begin(); it != channelList.end(); it++) {
			if (!(*it)->isOnChan(&user)) {
				(*it)->send(from + " JOIN " + (*it)->getName() + "\n");
				(*it)->addUser(static_cast<User *>(&sender));
				for (set<User *>::const_iterator users = (*it)->getUsers().begin(); users != (*it)->getUsers().end(); users++) {
					user.send(ResponseTypes::RPL_NAMREPLY((*it)->getName().c_str(), (*users)->getName().c_str()));
				}
				user.send(ResponseTypes::RPL_TOPIC((*it)->getName().c_str(), (*it)->getTopic().c_str()));
			}
		}
	}
};

#endif /* FT_IRC_CORE_JOIN_COMMAND */
