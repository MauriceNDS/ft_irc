#include "core/command/PartCommand.hpp"

#include "core/Irc.hpp"

#include "api/User.hpp"
#include "api/Channel.hpp"
#include "api/ResponseTypes.hpp"

void PartCommand::execute(const Command& cmd, CommandSender& sender) {
	User &user = static_cast<User &>(sender);

	string *message = cmd.getArg<string *>("message");
	vector<Channel *>& channelList = cmd.getArg<vector<Channel *> >("channels");
	for (vector<Channel *>::iterator it = channelList.begin(); it != channelList.end(); it++) {
		Channel *channel = *it;

		if (!channel->containsUser(user)) {
			sender.send(ResponseTypes::ERR_NOTONCHANNEL(channel->getName().c_str()));
			continue;
		}

		if (channel->getFlags().anonymous)
			channel->send(ResponseTypes::PART.anonymous("anonymous", message ? message->c_str() : ""));
		else
			channel->send(ResponseTypes::PART(sender, channel->getName().c_str(), message ? message->c_str() : user.getSenderName().c_str()));

		channel->removeUser(user);
	}
}
