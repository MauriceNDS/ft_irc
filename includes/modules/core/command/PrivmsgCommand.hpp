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
		User &user = static_cast<User &>(sender);

		vector<CommandSender *>& target = cmd.getArg<vector<CommandSender *> >("msgtarget");
		string from = user.getNickName() + "!" + user.getUserName() + "@" + Irc::getInstance().getServer().getHost();
		string message = cmd.getArg<string>("message") + "\n";

		for (vector<CommandSender *>::iterator it = target.begin(); it != target.end(); it++) {
			if (Channel::isValidIdentifier((*it)->getName())) {
				if (Irc::getInstance().getChannels().find((*it)->getName()) != Irc::getInstance().getChannels().end()) {
					if (!Irc::getInstance().getChannels().find((*it)->getName())->second->isOnChan(static_cast<User *>(&sender)) && Irc::getInstance().getChannels().find((*it)->getName())->second->getFlag().outside_message) {
						sender.send(ResponseTypes::ERR_NOTONCHANNEL((*it)->getName().c_str(), sender.getName().c_str()));
						continue ;
					} else if (Irc::getInstance().getChannels().find((*it)->getName())->second->getFlag().moderate && !Irc::getInstance().getChannels().find((*it)->getName())->second->isVoiceOp(&user)) {
						sender.send(ResponseTypes::ERR_CANNOTSENDTOCHAN((*it)->getName().c_str()));
						continue ;
					}
				}
			}
			(*it)->send(from + " PRIVMSG " + (*it)->getName() + " :" + message.c_str());
		}
	}
};

#endif /* FT_IRC_CORE_PRIVMSG_COMMAND */
