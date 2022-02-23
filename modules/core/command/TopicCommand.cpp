#include "core/command/TopicCommand.hpp"

void TopicCommand::execute(const Command& cmd, CommandSender& sender) {
	User& user = static_cast<User&>(sender);

	Channel& channel = cmd.getArg<Channel>("channel");
	string *topic = cmd.getArg<string *>("topic");
	if (!channel.isOnChan(static_cast<User *>(&sender))) {
		sender.send(ResponseTypes::ERR_NOTONCHANNEL(channel.getName().c_str()));
		return;
	}
	else if (topic) {
		if (channel.getFlag().topic && !channel.isChanop(static_cast<User *>(&sender))) {
			sender.send(ResponseTypes::ERR_CHANOPRIVSNEEDED(channel.getName().c_str()));
			return;
		}
		channel.setTopic(*topic);
	} else if (channel.getFlag().topic) {
		if (!channel.getFlag().secret)
			user.send(ResponseTypes::RPL_TOPIC(channel.getName().c_str(), channel.getTopic().c_str()));
	} else {
		user.send(ResponseTypes::ERR_NOCHANMODES(channel.getName().c_str()));
	}
}
