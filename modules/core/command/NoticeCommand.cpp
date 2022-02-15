#include "core/command/NoticeCommand.hpp"

void NoticeCommand::execute(const Command& cmd, CommandSender& sender) {
	User &user = static_cast<User &>(sender);
	string from = user.getName() + "!" + user.getUserName() + "@" + Irc::getInstance().getServer().getHost();

	vector<CommandSender *>& target = cmd.getArg<vector<CommandSender *> >("msgtarget");
	string& message = cmd.getArg<string>("message");

	for (vector<CommandSender *>::iterator it = target.begin(); it != target.end(); it++) {
		if(Channel::isValidIdentifier((*it)->getName())) {
			if (Irc::getInstance().getChannels().find((*it)->getName()) != Irc::getInstance().getChannels().end()) {
				if (!Irc::getInstance().getChannels().find((*it)->getName())->second->isOnChan(static_cast<User *>(&sender))) {
					continue ;
				}
			}
		}
		if (Irc::getInstance().getChannels().find((*it)->getName())->second->getFlag().anonymous) {
			(*it)->send(ResponseTypes::NOTICE.anonymous((*it)->getName().c_str(), message.c_str()));	
		} else {
			(*it)->send(ResponseTypes::NOTICE(sender, (*it)->getName().c_str(), message.c_str()));
		}
	}
}