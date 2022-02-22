#include "core/command/NoticeCommand.hpp"

void NoticeCommand::execute(const Command& cmd, CommandSender& sender) {
	User &user = static_cast<User &>(sender);

	vector<CommandSender *>& target = cmd.getArg<vector<CommandSender *> >("msgtarget");
	string& message = cmd.getArg<string>("message");

	for (vector<CommandSender *>::iterator it = target.begin(); it != target.end(); it++) {
		const string& identifier = (*it)->getSenderName();
		Channel *channel = Irc::getInstance().findChannel(identifier);

		if (channel) {
			if (!channel->isOnChan(&user) && channel->getFlag().outside_message) {
				continue;
			} else if (channel->getFlag().moderate && !channel->isVoiceOp(&user)) {
				continue;
			} else if (channel->getFlag().anonymous) {
				(*it)->send(ResponseTypes::NOTICE.anonymous(identifier.c_str(), message.c_str()));	
				continue;
			}
		}
		(*it)->send(ResponseTypes::NOTICE(sender, identifier.c_str(), message.c_str()));
	}
}
