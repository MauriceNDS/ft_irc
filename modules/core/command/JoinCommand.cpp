#include "core/command/JoinCommand.hpp"

#include "api/User.hpp"
#include "api/Channel.hpp"
#include "api/ResponseTypes.hpp"

void JoinCommand::execute(const Command& cmd, CommandSender& sender) {
	User& user = static_cast<User&>(sender);

	vector<Channel *>& channelList = cmd.getArg<vector<Channel *> >("channels");
	vector<string *> *passwords = cmd.getArg<vector<string *> *>("keys");
	size_t arg_n = 0;
	for (vector<Channel *>::iterator it = channelList.begin(); it != channelList.end(); it++) {
		Channel *channel = *it;

		++arg_n;
		if (!channel->getPassword().empty()) {
			if (!passwords || arg_n > passwords->size()) {
				user.send(ResponseTypes::ERR_BADCHANNELKEY(channel->getName().c_str()));
				continue;
			}
			string password = *(*passwords)[arg_n - 1];
			if (password != channel->getPassword()) {
				user.send(ResponseTypes::ERR_BADCHANNELKEY(channel->getName().c_str()));
				continue;
			}
		}
		channel->addUser(user);
	}
}
