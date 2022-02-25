#include "core/command/ListCommand.hpp"

#include "core/Irc.hpp"

#include "api/Channel.hpp"
#include "api/ResponseTypes.hpp"

void ListCommand::sendChan(const Channel *channel, const CommandSender& sender) const {
	if (!channel->getFlags().secret || !channel->getFlags().priv)
		sender.send(ResponseTypes::RPL_LIST(sender.getName().c_str(), channel->getName().c_str(), ::itos(channel->getUsers().size()).c_str(), channel->getTopic().c_str()));
}

void ListCommand::execute(const Command& cmd, CommandSender& sender) {
	vector<Channel *> *channelList = cmd.getArg<vector<Channel *> *>("channels");
	if (!channelList) {
		const map<string, Channel *>& channelList = Irc::getInstance().getChannels();

		for (map<string, Channel *>::const_iterator it = channelList.begin(); it != channelList.end(); it++)
			sendChan(it->second, sender);
	} else {
		for (vector<Channel *>::iterator it = channelList->begin(); it != channelList->end(); it++)
			sendChan(*it, sender);
	}
	sender.send(ResponseTypes::RPL_LISTEND(sender.getName().c_str()));
}
