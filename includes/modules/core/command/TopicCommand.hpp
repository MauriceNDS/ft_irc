#ifndef FT_IRC_CORE_TOPIC_COMMAND
#define FT_IRC_CORE_TOPIC_COMMAND

#include "ft_irc.hpp"

#include "core/Irc.hpp"

#include "api/ResponseTypes.hpp"
#include "api/User.hpp"
#include "api/command/CommandExecutor.hpp"

#include "api/ResponseTypes.hpp"

class TopicCommand : public CommandExecutor {

	void execute(const Command& cmd, CommandSender& sender) {
		User& user = static_cast<User&>(sender);

        Channel *channel = cmd.getArg<Channel *>("channel");
        string *topic = cmd.getArg<string *>("topic");
        if (!channel->isOnChan(static_cast<User *>(&sender))) {
            sender.send(ResponseTypes::ERR_NOTONCHANNEL(channel->getName().c_str()));
            return ;
        }
        else if (topic) {
            if (!channel->isChanop(static_cast<User *>(&sender))) {
                sender.send(ResponseTypes::ERR_CHANOPRIVSNEEDED(channel->getName().c_str()));
                return ;
            }
            channel->setTopic(*topic);
        } else {
		    user.send(ResponseTypes::RPL_TOPIC(channel->getName().c_str(), channel->getTopic().c_str()));
        }
	}
};

#endif /* FT_IRC_CORE_TOPIC_COMMAND */