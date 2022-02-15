#include "core/command/ListCommand.hpp"

void ListCommand::execute(const Command& cmd, CommandSender& sender) {
	User& user = static_cast<User&>(sender);

	vector<Channel *> *channelList = cmd.getArg<vector<Channel *> *>("channels");
	if (!channelList) {
		const map<string, Channel *>& channelList = Irc::getInstance().getChannels();

		for (map<string, Channel *>::const_iterator it = channelList.begin(); it != channelList.end(); it++) {
			user.send(ResponseTypes::RPL_LIST(it->first.c_str(), it->second->getTopic().c_str()));
		}
		user.send(ResponseTypes::RPL_LISTEND());
	} else {
		for (vector<Channel *>::iterator it = channelList->begin(); it != channelList->end(); it++) {
			user.send(ResponseTypes::RPL_LIST((*it)->getName().c_str(), (*it)->getTopic().c_str()));
		}
		user.send(ResponseTypes::RPL_LISTEND());
	}	
}