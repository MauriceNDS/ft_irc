#ifndef FT_IRC_CORE_PRIVMSG_COMMAND
#define FT_IRC_CORE_PRIVMSG_COMMAND

#include "ft_irc.hpp"

#include "core/Irc.hpp"

#include "api/ResponseTypes.hpp"
#include "api/User.hpp"
#include "api/command/CommandExecutor.hpp"
#include "core/command/elements/MsgToCommandElement.hpp"

#include "api/ResponseTypes.hpp"

class PrivmsgCommand : public CommandExecutor {

	void execute(const Command& cmd, CommandSender& sender) {
		User& user = static_cast<User&>(sender);

        vector<CommandSender *> target = cmd.getArg<vector<CommandSender *> >("msgtarget");
        string& message = cmd.getArg<string &>("message");

		for (vector<CommandSender *>::iterator it = target.begin(); it != target.end(); it++) {
            try {
                Channel *channel = dynamic_cast<Channel *>(*it);
                if (!channel->isOnChan(static_cast<User *>(&sender))) {
                    sender.send(ResponseTypes::ERR_NOTONCHANNEL((*it)->getName().c_str(), sender.getName().c_str()));
                    continue ;
                }
            } catch(std::bad_cast& e){}
			(*it)->send(message.c_str());
		}
	}
};

#endif /* FT_IRC_CORE_PRIVMSG_COMMAND */