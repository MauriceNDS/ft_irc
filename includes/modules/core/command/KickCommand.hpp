#ifndef FT_IRC_CORE_KICK_COMMAND
#define FT_IRC_CORE_KICK_COMMAND

#include "ft_irc.hpp"

#include "core/Irc.hpp"

#include "api/User.hpp"
#include "api/command/CommandExecutor.hpp"

#include "api/ResponseTypes.hpp"

class KickCommand : public CommandExecutor {

	void execute(const Command& cmd, CommandSender& sender) {

		string *message = cmd.getArg<string *>("message");
		Channel *channel = cmd.getArg<Channel *>("channel");
		User *user = cmd.getArg<User *>("user");
		if (!channel) {
			sender.send(ResponseTypes::ERR_NOSUCHCHANNEL());
			return ;
		} else if (!channel->isChanop(static_cast<User *>(&sender))) {
			sender.send(ResponseTypes::ERR_CHANOPRIVSNEEDED(channel->getName().c_str()));
			return ;
		}
		channel->removeUser(user);
		if (message) {
			channel->send(*message);
		} else {
			channel->send(user->getName().c_str());
		}
	}
};

#endif /* FT_IRC_CORE_KICK_COMMAND */
