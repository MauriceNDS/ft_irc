#include "core/command/KickCommand.hpp"

#include "api/User.hpp"
#include "api/Channel.hpp"
#include "api/ResponseTypes.hpp"

void KickCommand::execute(const Command& cmd, CommandSender& sender) {
	User &user = static_cast<User &>(sender);

	string *message = cmd.getArg<string *>("message");
	Channel& channel = cmd.getArg<Channel>("channel");
	User& target = cmd.getArg<User>("user");
	
	if (!channel.isChanop(&user)) {
		// If user is not an operator
		sender.send(ResponseTypes::ERR_CHANOPRIVSNEEDED(channel.getName().c_str()));
		return;
	} else if (!channel.isOnChan(&target)) {
		// If target is not on the channel
		user.send(ResponseTypes::ERR_USERNOTINCHANNEL(target.getName().c_str(), channel.getName().c_str()));
		return ;
	}

	if (channel.getFlags().anonymous && message) {
		channel.send(ResponseTypes::KICK.anonymous(channel.getName().c_str(), message->c_str()));
	} else if (channel.getFlags().anonymous && !message) {
		channel.send(ResponseTypes::KICK.anonymous(channel.getName().c_str(), target.getName().c_str()));
	} if (message) {
		channel.send(ResponseTypes::KICK(sender, channel.getName().c_str(), message->c_str()));
	} else {
		channel.send(ResponseTypes::KICK(sender, channel.getName().c_str(), target.getName().c_str()));
	}
	channel.removeUser(&target);
}
