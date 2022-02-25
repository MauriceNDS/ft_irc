#include "core/command/PrivmsgCommand.hpp"

#include "api/User.hpp"
#include "api/Channel.hpp"
#include "api/ResponseTypes.hpp"

void PrivmsgCommand::execute(const Command& cmd, CommandSender& sender) {
	User& user = static_cast<User &>(sender);
	vector<CommandSender *>& target = cmd.getArg<vector<CommandSender *> >("msgtarget");
	string message = cmd.getArg<string>("message");
	for (vector<CommandSender *>::iterator it = target.begin(); it != target.end(); it++) {
		Channel *channel = dynamic_cast<Channel *>(*it);
		if (channel) {
			if (!channel->isOnChan(&user) && !channel->getFlags().outside_message)
				sender.send(ResponseTypes::ERR_NOTONCHANNEL(channel->getName().c_str(), channel->getName().c_str()));
			else if (channel->getFlags().moderate && !channel->isVoiceOp(&user))
				sender.send(ResponseTypes::ERR_CANNOTSENDTOCHAN(channel->getName().c_str()));
			else if (channel->getFlags().anonymous)
				channel->send(sender, ResponseTypes::PRIVMSG.anonymous("anonymous", message.c_str()));
			else
				channel->send(sender, ResponseTypes::PRIVMSG(sender, channel->getName().c_str(), message.c_str()));
			continue;
		}
		User *target = dynamic_cast<User *>(*it);
		if (target) {
			target->send(ResponseTypes::PRIVMSG(sender, target->getName().c_str(), message.c_str()));
			continue;
		}
	}
}
