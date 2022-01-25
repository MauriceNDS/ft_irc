#ifndef FT_IRC_CORE_JOIN_COMMAND
#define FT_IRC_CORE_JOIN_COMMAND

#include "ft_irc.hpp"

#include "core/Irc.hpp"

#include "api/User.hpp"
#include "api/command/CommandExecutor.hpp"

#include "server/Response.hpp"

class JoinCommand : public CommandExecutor {

	Response execute(const Command& cmd, CommandSender& sender) {

        vector<string> channelList = cmd.getArg<vector<string> >("channels");
		for (vector<string>::iterator it = channelList.begin(); it != channelList.end(); it++)
		{
			Channel * chan = Irc::getInstance().findChannel(*it);
			if (!chan)
			{
				Irc::getInstance().addChannel(new Channel(*it));
				chan = Irc::getInstance().findChannel(*it);
				chan->addUser(dynamic_cast<User *>(&sender));
			}
			else
				chan->addUser(dynamic_cast<User *>(&sender));
		}
		return RPL_NONE;
	}
};

#endif /* FT_IRC_CORE_JOIN_COMMAND */