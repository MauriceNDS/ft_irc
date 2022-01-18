#ifndef FT_IRC_CORE_NICK_COMMAND
#define FT_IRC_CORE_NICK_COMMAND

#include "ft_irc.hpp"

#include "core/Irc.hpp"

#include "api/User.hpp"
#include "api/command/CommandExecutor.hpp"

#include "server/Response.hpp"

class NickCommand : public CommandExecutor {

	Response execute(const Command& cmd, CommandSender& sender) {
		User& user = dynamic_cast<User&>(sender);

		string nickname = cmd.getArg<string>("nickname");
		if (nickname.empty() || nickname.find(' ') != string::npos)
			return ERR_ERRONEUSNICKNAME;

		user.setNickName(nickname);
		return RPL_NONE;
	}
};

#endif /* FT_IRC_CORE_NICK_COMMAND */
