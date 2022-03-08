#include "core/command/KickCommand.hpp"

#include "api/User.hpp"
#include "api/Channel.hpp"
#include "api/ResponseTypes.hpp"

void KickCommand::execute(const Command& cmd, CommandSender& sender) {
	User &user = static_cast<User &>(sender);

	string *message = cmd.getArg<string *>("message");
	Channel& channel = cmd.getArg<Channel>("channel");
	User& target = cmd.getArg<User>("user");
	
	if (!channel.isOperator(user)) {
		sender.send(ResponseTypes::ERR_CHANOPRIVSNEEDED(channel.getName().c_str()));
		return;
	} else if (!channel.containsUser(target)) {
		user.send(ResponseTypes::ERR_USERNOTINCHANNEL(target.getName().c_str(), channel.getName().c_str()));
		return ;
	}

	channel.send(ResponseTypes::KICK(sender, channel.getName().c_str(), message ? message->c_str() : target.getName().c_str()));

	channel.removeUser(target);
}
