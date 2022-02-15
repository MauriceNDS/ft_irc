#include "core/command/PrivmsgCommand.hpp"

void PrivmsgCommand::execute(const Command& cmd, CommandSender& sender) {
	User& user = static_cast<User &>(sender);
	vector<CommandSender *>& target = cmd.getArg<vector<CommandSender *> >("msgtarget");
	string message = cmd.getArg<string>("message") + "\n";
	for (vector<CommandSender *>::iterator it = target.begin(); it != target.end(); it++) {
		const string& identifier = (*it)->getName();
		Channel *channel = Irc::getInstance().findChannel(identifier);
		if (channel) {
			if (!channel->isOnChan(&user) && channel->getFlag().outside_message) {
				sender.send(ResponseTypes::ERR_NOTONCHANNEL(identifier.c_str(), sender.getName().c_str()));
				continue;
			} else if (channel->getFlag().moderate && !channel->isVoiceOp(&user)) {
				sender.send(ResponseTypes::ERR_CANNOTSENDTOCHAN(identifier.c_str()));
				continue;
			} else if (channel->getFlag().anonymous) {
				(*it)->send(ResponseTypes::PRIVMSG.anonymous(identifier.c_str(), message.c_str()));	
				continue;
			}
		}
		(*it)->send(ResponseTypes::PRIVMSG(sender, identifier.c_str(), message.c_str()));
	}
}
