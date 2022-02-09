#ifndef FT_IRC_CORE_KICK_COMMAND
#define FT_IRC_CORE_KICK_COMMAND

#include "ft_irc.hpp"

#include "core/Irc.hpp"

#include "api/User.hpp"
#include "api/command/CommandExecutor.hpp"

#include "api/ResponseTypes.hpp"

class KickCommand : public CommandExecutor {

	void execute(const Command& cmd, CommandSender& sender) {
		User &oper = static_cast<User &>(sender);
		string from = oper.getNickName() + "!" + oper.getUserName() + "@" + Irc::getInstance().getServer().getHost();

		string *message = cmd.getArg<string *>("message");
		Channel& channel = cmd.getArg<Channel>("channel");
		User& user = cmd.getArg<User>("user");
		if (!channel.isChanop(static_cast<User *>(&sender))) {
			sender.send(ResponseTypes::ERR_CHANOPRIVSNEEDED(channel.getName().c_str()));
			return;
		}
		else if (!channel.isOnChan(&user)) {
			oper.send(ResponseTypes::ERR_USERNOTINCHANNEL(user.getName().c_str(), channel.getName().c_str()));
			return ;
		}
		if (channel.getFlag().anonymous && message) {
			channel.send("anonymous!anonymous@anonymous KICK " + channel.getName() + " anonymous :" + *message + "\n");
		} else if (channel.getFlag().anonymous && !message) {
			channel.send("anonymous!anonymous@anonymous KICK " + channel.getName() + " anonymous :" + user.getName() + "\n");
		} if (message) {
			channel.send(from + " KICK " + channel.getName() + " " + user.getName() + " :" + *message + "\n");
		} else {
			channel.send(from + " KICK " + channel.getName() + " " + user.getName() + " :" + user.getName() + "\n");
		}
		channel.removeUser(&user);
	}
};

#endif /* FT_IRC_CORE_KICK_COMMAND */
