#include "core/command/KickCommand.hpp"

void KickCommand::execute(const Command& cmd, CommandSender& sender) {
	User &oper = static_cast<User &>(sender);

	string *message = cmd.getArg<string *>("message");
	Channel& channel = cmd.getArg<Channel>("channel");
	User& user = cmd.getArg<User>("user");
	if (!channel.isChanop(static_cast<User *>(&sender))) {
		sender.send(ResponseTypes::ERR_CHANOPRIVSNEEDED(channel.getName().c_str()));
		return;
	}
	else if (!channel.isOnChan(&user)) {
		oper.send(ResponseTypes::ERR_USERNOTINCHANNEL(user.getName().c_str(), channel.getName().c_str()));
		return ;
	}
	if (channel.getFlag().anonymous && message) {
		channel.send(ResponseTypes::KICK.anonymous(channel.getName().c_str(), message->c_str()));
	} else if (channel.getFlag().anonymous && !message) {
		channel.send(ResponseTypes::KICK.anonymous(channel.getName().c_str(), user.getName().c_str()));
	} if (message) {
		channel.send(ResponseTypes::KICK(sender, channel.getName().c_str(), message->c_str()));
	} else {
		channel.send(ResponseTypes::KICK(sender, channel.getName().c_str(), user.getName().c_str()));
	}
	channel.removeUser(&user);
}
