#ifndef FT_IRC_CORE_PART_COMMAND
#define FT_IRC_CORE_PART_COMMAND

#include "ft_irc.hpp"

#include "core/Irc.hpp"

#include "api/User.hpp"
#include "api/command/CommandExecutor.hpp"

#include "server/Response.hpp"

class PartCommand : public CommandExecutor {

	Response execute(const Command& cmd, CommandSender& sender) {
		User& user = static_cast<User&>(sender);

        string & message = cmd.getArg<string>("message");
        vector<Channel *> channelList = cmd.getArg<vector<Channel *> >("channels");
		for (vector<Channel *>::iterator it = channelList.begin(); it != channelList.end(); it++) {
			(*it)->removeUser(static_cast<User *>(&sender));
			(*it)->send(message);
		}
		return RPL_NONE;
	}
};

#endif /* FT_IRC_CORE_PART_COMMAND */