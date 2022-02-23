#include "core/command/ListCommand.hpp"

#include "core/Irc.hpp"

#include "api/Channel.hpp"
#include "api/ResponseTypes.hpp"

void ListCommand::execute(const Command& cmd, CommandSender& sender) {
	vector<Channel *> *channelList = cmd.getArg<vector<Channel *> *>("channels");
	if (!channelList) {
		const map<string, Channel *>& channelList = Irc::getInstance().getChannels();

		for (map<string, Channel *>::const_iterator it = channelList.begin(); it != channelList.end(); it++) {
			if (!it->second->getFlag().secret || !it->second->getFlag().priv)
				sender.send(ResponseTypes::RPL_LIST(it->first.c_str(), it->second->getTopic().c_str()));
		}
		sender.send(ResponseTypes::RPL_LISTEND());
	} else {
		for (vector<Channel *>::iterator it = channelList->begin(); it != channelList->end(); it++) {
			if (!(*it)->getFlag().secret)
				sender.send(ResponseTypes::RPL_LIST((*it)->getName().c_str(), (*it)->getTopic().c_str()));
		}
		sender.send(ResponseTypes::RPL_LISTEND());
	}	
}
