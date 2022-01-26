#ifndef FT_IRC_CORE_USER_COMMAND
#define FT_IRC_CORE_USER_COMMAND

#include "ft_irc.hpp"

#include "core/Irc.hpp"

#include "api/User.hpp"
#include "api/command/CommandExecutor.hpp"

#include "api/ResponseTypes.hpp"

class UserCommand : public CommandExecutor {

	void execute(const Command& cmd, CommandSender& sender) {
		User& user = dynamic_cast<User&>(sender);

		if (!(user.getUserName().empty())) {
			user.send(ResponseTypes::ERR_ALREADYREGISTRED());
			return;
		}

		user.setUserName(cmd.getArg<string>("user"));
		user.setRealName(cmd.getArg<string>("realname"));
	}
};

#endif /* FT_IRC_CORE_USER_COMMAND */
