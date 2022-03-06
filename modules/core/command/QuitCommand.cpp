#include "core/command/QuitCommand.hpp"

#include "core/Irc.hpp"

#include "api/User.hpp"
#include "api/Channel.hpp"
#include "api/ResponseTypes.hpp"

void QuitCommand::execute(const Command& cmd, CommandSender& sender) {
	User& user = static_cast<User &>(sender);

	// *************************************************
	// Subject to removal
	string *message = cmd.getArg<string *>("message");
	map<string, Channel *> chan_list = Irc::getInstance().getChannels();
	for (map<string, Channel *>::const_iterator it = chan_list.begin(); it != chan_list.end(); it++) {
		if (it->second->containsUser(user)) {
			if (message && it->second->getFlags().anonymous) {
				it->second->send(ResponseTypes::PART.anonymous(message->c_str()));
			} else if (it->second->getFlags().anonymous) {
				it->second->send(ResponseTypes::PART.anonymous("anonymous"));
			} else if (message) {
				it->second->send(ResponseTypes::QUIT(user, message->c_str()));
			} else {
				it->second->send(ResponseTypes::QUIT(user, user.getName().c_str()));
			}
		}
	}
	// *************************************************

	Irc::getInstance().removeUser(user);
}
