#include "core/command/QuitCommand.hpp"

void QuitCommand::execute(const Command& cmd, CommandSender& sender) {
	User& user = static_cast<User &>(sender);

	string *message = cmd.getArg<string *>("message");
	map<string, Channel *> chan_list = Irc::getInstance().getChannels();
	for (map<string, Channel *>::const_iterator it = chan_list.begin(); it != chan_list.end(); it++) {
		if (it->second->isOnChan(&user)) {
			if (message && it->second->getFlag().anonymous) {
				it->second->send(ResponseTypes::PART.anonymous(message->c_str()));
			} else if (it->second->getFlag().anonymous) {
				it->second->send(ResponseTypes::PART.anonymous("anonymous"));
			} else if (message) {
				it->second->send(ResponseTypes::QUIT(user, message->c_str()));
			} else {
				it->second->send(ResponseTypes::QUIT(user, user.getName().c_str()));
			}
		}
	}
	Client& client = static_cast<Client &>(sender);
	sender.send(ResponseTypes::ERROR());
	client.getConnection()->closeConnection = true;
}
