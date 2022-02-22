#include "core/command/InviteCommand.hpp"

#include "core/Irc.hpp"

#include "api/User.hpp"
#include "api/ResponseTypes.hpp"

void InviteCommand::execute(const Command& cmd, CommandSender& sender) {
	User &sending = static_cast<User &>(sender);

	string& channel_name = cmd.getArg<string>("channel");
	User& user = cmd.getArg<User>("nickname");
	map<string, Channel *>::const_iterator channel = Irc::getInstance().getChannels().find(channel_name);
	if (Irc::getInstance().getChannels().end() != channel) {
		if (channel->second->isOnChan(&user)) {
			sending.send(ResponseTypes::ERR_USERONCHANNEL(user.getName().c_str(), channel_name.c_str()));
			return ;
		} else if (!channel->second->isOnChan(&sending)) {
			sending.send(ResponseTypes::ERR_NOTONCHANNEL(sending.getName().c_str(), channel_name.c_str()));
			return ;
		}
		channel->second->addInvite(&user);
	}
	sending.send(ResponseTypes::RPL_INVITING(channel_name.c_str(), user.getName().c_str()));
	user.send(ResponseTypes::RPL_INVITING(channel_name.c_str(), user.getName().c_str()));
}
