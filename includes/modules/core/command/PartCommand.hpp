#ifndef FT_IRC_CORE_PART_COMMAND
#define FT_IRC_CORE_PART_COMMAND

#include "ft_irc.hpp"

#include "core/Irc.hpp"

#include "api/User.hpp"
#include "api/command/CommandExecutor.hpp"

#include "api/ResponseTypes.hpp"

class PartCommand : public CommandExecutor {

	void execute(const Command& cmd, CommandSender& sender) {
		User &user = static_cast<User &>(sender);
		string from = user.getNickName() + "!" + user.getUserName() + "@" + Irc::getInstance().getServer().getHost();

		string *message = cmd.getArg<string *>("message");
		vector<Channel *>& channelList = cmd.getArg<vector<Channel *> >("channels");
		for (vector<Channel *>::iterator it = channelList.begin(); it != channelList.end(); it++) {
			if (!*it) {
				sender.send(ResponseTypes::ERR_NOSUCHCHANNEL());
				continue ;
			}
			else if (!(*it)->isOnChan(&user)) {
				user.send(ResponseTypes::ERR_NOTONCHANNEL((*it)->getName().c_str()));
				continue ;
			}
			(*it)->removeUser(static_cast<User *>(&sender));
			if (message) {
				(*it)->send(from + " PART " + (*it)->getName() + " :" + *message + "\n");
			} else {
				(*it)->send(from + " PART " + (*it)->getName() + " :" + sender.getName() + "\n");
			}
		}
	}
};

#endif /* FT_IRC_CORE_PART_COMMAND */
