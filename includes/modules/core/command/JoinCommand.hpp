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
		vector<string *> *passwords = cmd.getArg<vector<string *> *>("keys");
		size_t arg_i = 0;
		for (vector<Channel *>::iterator it = channelList.begin(); it != channelList.end(); it++) {
			if ((*it)->getFlag().invite && (*it)->getInvite().find(&user) == (*it)->getInvite().end()) {
				user.send(ResponseTypes::ERR_INVITEONLYCHAN((*it)->getName().c_str()));
			} else if ((*it)->getFlag().user_limit && (*it)->getUsers().size() >= (*it)->getFlag().user_limit) {
				user.send(ResponseTypes::ERR_CHANNELISFULL((*it)->getName().c_str()));
			} else if (!(*it)->getPassword().empty() && (!passwords || (arg_i > passwords->size() || *((*passwords)[arg_i]) != (*it)->getPassword()))) {
				user.send(ResponseTypes::ERR_BADCHANNELKEY((*it)->getName().c_str()));
			} else if (!(*it)->isOnChan(&user)) {
				if (!(*it)->getFlag().anonymous) {
					(*it)->send(ResponseTypes::JOIN(user, (*it)->getName().c_str()));
				} else {
					(*it)->send(ResponseTypes::JOIN.anonymous((*it)->getName().c_str()));
				}
				for (set<User *>::const_iterator users = (*it)->getUsers().begin(); users != (*it)->getUsers().end(); users++) {
					user.send(ResponseTypes::RPL_NAMREPLY((*it)->getName().c_str(), (*users)->getName().c_str()));
				}
				(*it)->addUser(static_cast<User *>(&sender));
				user.send(ResponseTypes::RPL_TOPIC((*it)->getName().c_str(), (*it)->getTopic().c_str()));
			}
			arg_i++;
		}
	}
};

#endif /* FT_IRC_CORE_JOIN_COMMAND */
