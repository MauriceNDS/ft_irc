#ifndef FT_IRC_CORE_NAMES_COMMAND
#define FT_IRC_CORE_NAMES_COMMAND

#include "ft_irc.hpp"

#include "core/Irc.hpp"

#include "api/ResponseTypes.hpp"
#include "api/User.hpp"
#include "api/command/CommandExecutor.hpp"

#include "api/ResponseTypes.hpp"

class NamesCommand : public CommandExecutor {

	void execute(const Command& cmd, CommandSender& sender) {
		User& user = static_cast<User&>(sender);

		vector<Channel *> *channelList = cmd.getArg<vector <Channel *> *>("channels");
		if (!channelList) {
			const map<string, Channel *>& channelList = Irc::getInstance().getChannels();
			const vector<User *>& userList = Irc::getInstance().getUsers();

			for (map<string, Channel *>::const_iterator it = channelList.begin(); it != channelList.end(); it++) {
				const set<User *>& channelUserList = it->second->getUsers();

				for (set<User *>::const_iterator ite = channelUserList.begin(); ite != channelUserList.end(); ite++) {
					user.send(ResponseTypes::RPL_NAMREPLY(it->first.c_str(), (*ite)->getNickName().c_str()));
				}
				user.send(ResponseTypes::RPL_ENDOFNAMES(it->first.c_str()));
			}
			for (vector<User *>::const_iterator it = userList.begin(); it != userList.end(); it++) {
				user.send(ResponseTypes::RPL_NAMREPLY("*", (*it)->getNickName().c_str()));
			}
			user.send(ResponseTypes::RPL_ENDOFNAMES("*"));
		} else {
			for (vector<Channel *>::const_iterator it = channelList->begin(); it != channelList->end(); it++) {
				const set<User *>& channelUserList = (*it)->getUsers();

				for (set<User *>::const_iterator ite = channelUserList.begin(); ite != channelUserList.end(); ite++) {
					user.send(ResponseTypes::RPL_NAMREPLY((*it)->getName().c_str(), (*ite)->getNickName().c_str()));
				}
				user.send(ResponseTypes::RPL_ENDOFNAMES((*it)->getName().c_str()));
			}
		}
	}
};

#endif /* FT_IRC_CORE_NAMES_COMMAND */
