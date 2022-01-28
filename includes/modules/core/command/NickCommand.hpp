#ifndef FT_IRC_CORE_NICK_COMMAND
#define FT_IRC_CORE_NICK_COMMAND

#include "ft_irc.hpp"

#include "core/Irc.hpp"

#include "api/User.hpp"
#include "api/command/CommandExecutor.hpp"

#include "api/ResponseTypes.hpp"

class NickCommand : public CommandExecutor {

	void execute(const Command& cmd, CommandSender& sender) {
		User& user = dynamic_cast<User&>(sender);

		string nickname = cmd.getArg<string>("nickname");
		if (nickname.empty() || nickname.find(' ') != string::npos) {
			user.send(ResponseTypes::ERR_ERRONEUSNICKNAME(nickname.c_str()));
			return;
		}

		user.setNickName(nickname);

		if (user.isRegistered())
			user.send(ResponseTypes::RPL_WELCOME(user.getNickName().c_str(), user.getUserName().c_str(), Irc::getInstance().getServer().getName().c_str()));
	}
};

#endif /* FT_IRC_CORE_NICK_COMMAND */
