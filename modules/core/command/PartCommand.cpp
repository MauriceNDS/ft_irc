#include "core/command/PartCommand.hpp"

void PartCommand::execute(const Command& cmd, CommandSender& sender) {
	User &user = static_cast<User &>(sender);
	string from = user.getName() + "!" + user.getUserName() + "@" + Irc::getInstance().getServer().getHost();

	string *message = cmd.getArg<string *>("message");
	vector<Channel *>& channelList = cmd.getArg<vector<Channel *> >("channels");
	for (vector<Channel *>::iterator it = channelList.begin(); it != channelList.end(); it++) {
		if (!*it) {
			sender.send(ResponseTypes::ERR_NOSUCHCHANNEL());
			continue ;
		}
		else if (!(*it)->isOnChan(&user)) {
			user.send(ResponseTypes::ERR_NOTONCHANNEL((*it)->getName().c_str()));
			continue ;
		}
		(*it)->removeUser(static_cast<User *>(&sender));
		if ((*it)->getFlag().anonymous && message) {
			(*it)->send(ResponseTypes::PART.anonymous((*it)->getName().c_str(), message->c_str()));
		} else if ((*it)->getFlag().anonymous && !message) {
			(*it)->send(ResponseTypes::PART.anonymous((*it)->getName().c_str(), "anonymous"));
		} else if (message) {
			(*it)->send(ResponseTypes::PART(sender, (*it)->getName().c_str(), message->c_str()));
		} else {
			(*it)->send(ResponseTypes::PART(sender, (*it)->getName().c_str(), user.getName().c_str()));
		}
	}
}
