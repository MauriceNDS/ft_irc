#include "core/command/NoticeCommand.hpp"

#include "api/User.hpp"
#include "api/Channel.hpp"
#include "api/ResponseTypes.hpp"

void NoticeCommand::execute(const Command& cmd, CommandSender& sender) {
	User &user = static_cast<User &>(sender);

	vector<CommandSender *>& target = cmd.getArg<vector<CommandSender *> >("msgtarget");
	string& message = cmd.getArg<string>("message");

	for (vector<CommandSender *>::iterator it = target.begin(); it != target.end(); it++) {
		Channel *channel = dynamic_cast<Channel *>(*it);
		if (channel) {
			if (!channel->isOnChan(&user) && channel->getFlag().outside_message) {}
			else if (channel->getFlag().moderate && !channel->isVoiceOp(&user)) {}
			else if (channel->getFlag().anonymous)
				channel->send(ResponseTypes::NOTICE.anonymous(channel->getName().c_str(), message.c_str()));
			else
				channel->send(ResponseTypes::NOTICE(sender, channel->getName().c_str(), message.c_str()));
			continue;
		}
		User *target = dynamic_cast<User *>(*it);
		if (target) {
			target->send(ResponseTypes::NOTICE(sender, target->getName().c_str(), message.c_str()));
			continue;
		}
	}
}
