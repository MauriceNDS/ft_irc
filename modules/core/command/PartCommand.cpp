#include "core/command/PartCommand.hpp"

void PartCommand::execute(const Command& cmd, CommandSender& sender) {
	User &user = static_cast<User &>(sender);

	string *message = cmd.getArg<string *>("message");
	vector<Channel *>& channelList = cmd.getArg<vector<Channel *> >("channels");
	for (vector<Channel *>::iterator it = channelList.begin(); it != channelList.end(); it++) {
		const string& identifier = (*it)->getSenderName();

		if (!*it) {
			sender.send(ResponseTypes::ERR_NOSUCHCHANNEL());
			continue ;
		}
		else if (!(*it)->isOnChan(&user)) {
			user.send(ResponseTypes::ERR_NOTONCHANNEL(identifier.c_str()));
			continue ;
		}
		(*it)->removeUser(static_cast<User *>(&sender));
		if ((*it)->getFlag().anonymous && message) {
			(*it)->send(ResponseTypes::PART.anonymous(identifier.c_str(), message->c_str()));
		} else if ((*it)->getFlag().anonymous && !message) {
			(*it)->send(ResponseTypes::PART.anonymous(identifier.c_str(), "anonymous"));
		} else if (message) {
			(*it)->send(ResponseTypes::PART(sender, identifier.c_str(), message->c_str()));
		} else {
			(*it)->send(ResponseTypes::PART(sender, identifier.c_str(), user.getSenderName().c_str()));
		}
	}
}
