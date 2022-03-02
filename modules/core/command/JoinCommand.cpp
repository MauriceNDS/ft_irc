#include "core/command/JoinCommand.hpp"

#include "api/User.hpp"
#include "api/Channel.hpp"
#include "api/ResponseTypes.hpp"

void JoinCommand::execute(const Command& cmd, CommandSender& sender) {
	User& user = static_cast<User&>(sender);

	vector<Channel *>& channelList = cmd.getArg<vector<Channel *> >("channels");
	vector<string *> *passwords = cmd.getArg<vector<string *> *>("keys");
	size_t arg_i = 0;
	for (vector<Channel *>::iterator it = channelList.begin(); it != channelList.end(); it++) {
		Channel *channel = *it;

		if (channel->getFlags().invite && channel->getInvites().find(&user) == channel->getInvites().end()) {
			user.send(ResponseTypes::ERR_INVITEONLYCHAN(channel->getName().c_str()));
		} else if (channel->getFlags().user_limit && channel->getUsers().size() >= channel->getFlags().user_limit) {
			user.send(ResponseTypes::ERR_CHANNELISFULL(channel->getName().c_str()));
		} else if (!channel->getPassword().empty() && (!passwords || (arg_i > passwords->size() || *((*passwords)[arg_i]) != channel->getPassword()))) {
			user.send(ResponseTypes::ERR_BADCHANNELKEY(channel->getName().c_str()));
		} else if (!channel->isOnChan(&user)) {
			channel->addUser(static_cast<User *>(&sender));
			if (!channel->getFlags().anonymous)
				channel->send(ResponseTypes::JOIN(user, channel->getName().c_str()));
			else
				channel->send(ResponseTypes::JOIN.anonymous(channel->getName().c_str()));

			for (set<User *>::const_iterator users = channel->getUsers().begin(); users != channel->getUsers().end(); users++) {
				if (!channel->getFlags().anonymous)
					user.send(ResponseTypes::RPL_NAMREPLY(user.getName().c_str(), channel->getSymbol().c_str(), channel->getName().c_str(), channel->getTaggedUserName((*users)).c_str()));
				else
					user.send(ResponseTypes::RPL_NAMREPLY("anonymous", channel->getSymbol().c_str(), channel->getName().c_str(), (*users)->getName().c_str()));
			}
			user.send(ResponseTypes::RPL_ENDOFNAMES(user.getName().c_str(), channel->getName().c_str()));
		}
		arg_i++;
	}
}
