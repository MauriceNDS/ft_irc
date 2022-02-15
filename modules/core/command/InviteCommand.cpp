#include "core/command/InviteCommand.hpp"

#include "core/Irc.hpp"

#include "api/User.hpp"
#include "api/Channel.hpp"
#include "api/ResponseTypes.hpp"

void InviteCommand::execute(const Command& cmd, CommandSender& sender) {
	User &user = static_cast<User &>(sender);

	string& channel_name = cmd.getArg<string>("channel");
	User& target = cmd.getArg<User>("nickname");
	map<string, Channel *>::const_iterator channel = Irc::getInstance().getChannels().find(channel_name);
	if (Irc::getInstance().getChannels().end() != channel) {
		if (channel->second->containsUser(&target)) {
			user.send(ResponseTypes::ERR_USERONCHANNEL(user.getName().c_str(), target.getName().c_str(), channel_name.c_str()));
			return;
		} else if (!channel->second->containsUser(&user)) {
			user.send(ResponseTypes::ERR_NOTONCHANNEL(user.getName().c_str(), user.getName().c_str(), channel_name.c_str()));
			return;
		}
		channel->second->addInvite(&target);
	}
	user.send(ResponseTypes::RPL_INVITING(user.getName().c_str(), target.getName().c_str(), channel_name.c_str()));
	target.send(ResponseTypes::RPL_INVITING(user.getName().c_str(), target.getName().c_str(), channel_name.c_str()));
}
