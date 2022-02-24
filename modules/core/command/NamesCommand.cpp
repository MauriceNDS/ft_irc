#include "core/command/NamesCommand.hpp"

#include "core/Irc.hpp"

#include "api/User.hpp"
#include "api/Channel.hpp"
#include "api/ResponseTypes.hpp"

void NamesCommand::execute(const Command& cmd, CommandSender& sender) {
	vector<Channel *> *channelList = cmd.getArg<vector<Channel *> *>("channels");
	if (!channelList) {
		const map<string, Channel *>& channelList = Irc::getInstance().getChannels();
		const vector<User *>& userList = Irc::getInstance().getUsers();

		for (map<string, Channel *>::const_iterator it = channelList.begin(); it != channelList.end(); it++) {
			const set<User *>& channelUserList = it->second->getUsers();

			if (it->second->getFlag().anonymous || it->second->getFlag().secret || it->second->getFlag().priv)
				continue;

			for (set<User *>::const_iterator ite = channelUserList.begin(); ite != channelUserList.end(); ite++) {
				sender.send(ResponseTypes::RPL_NAMREPLY(it->first.c_str(), (*ite)->getName().c_str()));
			}
			sender.send(ResponseTypes::RPL_ENDOFNAMES(it->first.c_str()));
		}
		for (vector<User *>::const_iterator it = userList.begin(); it != userList.end(); it++) {
			sender.send(ResponseTypes::RPL_NAMREPLY("*", (*it)->getName().c_str()));
		}
		sender.send(ResponseTypes::RPL_ENDOFNAMES("*"));
	} else {
		for (vector<Channel *>::const_iterator it = channelList->begin(); it != channelList->end(); it++) {
			const set<User *>& channelUserList = (*it)->getUsers();
			
			if ((*it)->getFlag().anonymous || (*it)->getFlag().secret)
				continue;

			for (set<User *>::const_iterator ite = channelUserList.begin(); ite != channelUserList.end(); ite++) {
				sender.send(ResponseTypes::RPL_NAMREPLY((*it)->getName().c_str(), (*ite)->getName().c_str()));
			}
			sender.send(ResponseTypes::RPL_ENDOFNAMES((*it)->getName().c_str()));
		}
	}
}