#ifndef FT_IRC_CORE_PART_COMMAND
#define FT_IRC_CORE_PART_COMMAND

#include "ft_irc.hpp"

#include "core/Irc.hpp"

#include "api/User.hpp"
#include "api/command/CommandExecutor.hpp"

#include "api/ResponseTypes.hpp"

class PartCommand : public CommandExecutor {

	void execute(const Command& cmd, CommandSender& sender) {

		string *message = cmd.getArg<string *>("message");
		vector<Channel *>& channelList = cmd.getArg<vector<Channel *> >("channels");
		for (vector<Channel *>::iterator it = channelList.begin(); it != channelList.end(); it++) {
			if (!*it) {
				sender.send(ResponseTypes::ERR_NOSUCHCHANNEL());
				continue ;
			}
			(*it)->removeUser(static_cast<User *>(&sender));
			if (message) {
				(*it)->send(*message);
			} else {
				(*it)->send(sender.getName().c_str());
			}
		}
	}
};

#endif /* FT_IRC_CORE_PART_COMMAND */
