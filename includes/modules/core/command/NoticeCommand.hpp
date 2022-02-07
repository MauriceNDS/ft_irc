#ifndef FT_IRC_CORE_NOTICE_COMMAND
#define FT_IRC_CORE_NOTICE_COMMAND

#include "ft_irc.hpp"

#include "core/Irc.hpp"

#include "api/ResponseTypes.hpp"
#include "api/User.hpp"
#include "api/command/CommandExecutor.hpp"
#include "core/command/elements/MsgToCommandElement.hpp"

#include "api/ResponseTypes.hpp"

class NoticeCommand : public CommandExecutor {

	void execute(const Command& cmd, CommandSender& sender) {

		vector<CommandSender *>& target = cmd.getArg<vector<CommandSender *> >("msgtarget");
		string& message = cmd.getArg<string>("message");

		for (vector<CommandSender *>::iterator it = target.begin(); it != target.end(); it++) {
			try {
				Channel *channel = dynamic_cast<Channel *>(*it);
				if (!channel->isOnChan(static_cast<User *>(&sender))) {
					continue ;
				}
			} catch(std::bad_cast& e){}
			(*it)->send(message.c_str());
		}
	}
};

#endif /* FT_IRC_CORE_NOTICE_COMMAND */
