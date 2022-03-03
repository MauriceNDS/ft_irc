#include "core/command/NamesCommand.hpp"

#include "core/Irc.hpp"

#include "api/User.hpp"
#include "api/Channel.hpp"
#include "api/ResponseTypes.hpp"

void NamesCommand::execute(const Command& cmd, CommandSender& sender) {
	vector<Channel *> *channelList = cmd.getArg<vector<Channel *> *>("channels");
	if (!channelList) {
		const map<string, Channel *>& channels = Irc::getInstance().getChannels();
		const vector<User *>& users = Irc::getInstance().getUsers();

		for (map<string, Channel *>::const_iterator it = channels.begin(); it != channels.end(); it++) {
			const Channel *channel = it->second;
			const set<User *>& channelUserList = channel->getUsers();

			if (channel->getFlags().anonymous || channel->getFlags().secret || channel->getFlags().priv)
				continue;

			for (set<User *>::const_iterator ite = channelUserList.begin(); ite != channelUserList.end(); ite++) {
				sender.send(ResponseTypes::RPL_NAMREPLY(sender.getName().c_str(), channel->getSymbol().c_str(), channel->getName().c_str(), channel->getTaggedUserName(*ite).c_str()));
			}
			sender.send(ResponseTypes::RPL_ENDOFNAMES(sender.getName().c_str(), channel->getName().c_str()));
		}
		for (vector<User *>::const_iterator it = users.begin(); it != users.end(); it++) {
			const User *user = *it;
			sender.send(ResponseTypes::RPL_NAMREPLY(sender.getName().c_str(), "=", "*", user->getName().c_str()));
		}
		sender.send(ResponseTypes::RPL_ENDOFNAMES(sender.getName().c_str(), "*"));
	} else {
		for (vector<Channel *>::const_iterator it = channelList->begin(); it != channelList->end(); it++) {
			const Channel *channel = *it;
			const set<User *>& channelUserList = channel->getUsers();
			
			if (channel->getFlags().anonymous || channel->getFlags().secret)
				continue;

			for (set<User *>::const_iterator ite = channelUserList.begin(); ite != channelUserList.end(); ite++) {
				sender.send(ResponseTypes::RPL_NAMREPLY(sender.getName().c_str(), channel->getSymbol().c_str(), channel->getName().c_str(), channel->getTaggedUserName(*ite).c_str()));
			}
			sender.send(ResponseTypes::RPL_ENDOFNAMES(sender.getName().c_str(), channel->getName().c_str()));
		}
	}
}
