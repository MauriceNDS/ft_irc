#include "core/command/PartCommand.hpp"

#include "api/User.hpp"
#include "api/Channel.hpp"
#include "api/ResponseTypes.hpp"

void PartCommand::execute(const Command& cmd, CommandSender& sender) {
	User &user = static_cast<User &>(sender);

	string *message = cmd.getArg<string *>("message");
	vector<Channel *>& channelList = cmd.getArg<vector<Channel *> >("channels");
	for (vector<Channel *>::iterator it = channelList.begin(); it != channelList.end(); it++) {
		Channel *channel = *it;

		if (!*it) {
			sender.send(ResponseTypes::ERR_NOSUCHCHANNEL());
			continue;
		} else if (!(*it)->isOnChan(&user)) {
			sender.send(ResponseTypes::ERR_NOTONCHANNEL(channel->getName().c_str()));
			continue;
		}
		channel->removeUser(&user);
		if (channel->getFlag().anonymous && message) {
			channel->send(ResponseTypes::PART.anonymous("anonymous", message->c_str()));
		} else if (channel->getFlag().anonymous && !message) {
			channel->send(ResponseTypes::PART.anonymous("anonymous"));
		} else if (message) {
			channel->send(ResponseTypes::PART(sender, channel->getName().c_str(), message->c_str()));
		} else {
			channel->send(ResponseTypes::PART(sender, channel->getName().c_str(), user.getSenderName().c_str()));
		}
	}
}
