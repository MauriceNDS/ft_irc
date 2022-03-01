#include "core/command/TopicCommand.hpp"

#include "api/User.hpp"
#include "api/Channel.hpp"
#include "api/ResponseTypes.hpp"

void TopicCommand::execute(const Command& cmd, CommandSender& sender) {
	User& user = static_cast<User&>(sender);

	Channel& channel = cmd.getArg<Channel>("channel");
	string *topic = cmd.getArg<string *>("topic");
	if (!channel.isOnChan(&user)) {
		sender.send(ResponseTypes::ERR_NOTONCHANNEL(channel.getName().c_str()));
		return;
	}
	else if (topic) {
		if (channel.getFlags().topic && !channel.isChanop(&user)) {
			sender.send(ResponseTypes::ERR_CHANOPRIVSNEEDED(channel.getName().c_str()));
			return;
		}
		channel.setTopic(*topic);
	} else if (channel.getFlags().topic) {
		if (!channel.getFlags().secret)
			user.send(ResponseTypes::RPL_TOPIC(sender.getName().c_str(), channel.getName().c_str(), channel.getTopic().c_str()));
	} else {
		user.send(ResponseTypes::ERR_NOCHANMODES(sender.getName().c_str(), channel.getName().c_str()));
	}
}
