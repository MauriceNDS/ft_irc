#include "core/command/ModeCommand.hpp"

#include "core/Irc.hpp"

#include "api/Flag.hpp"
#include "api/User.hpp"
#include "api/Channel.hpp"

#include "api/ResponseTypes.hpp"

void ModeCommand::execute(const Command& cmd, CommandSender& sender) {
	User& user = static_cast<User&>(sender);
	Channel& channel = cmd.getArg<Channel>("channel");
	vector<Flag> *modes = cmd.getArg<vector<Flag> *>("mode");

	Irc& irc = Irc::getInstance();
	Modes &flags = channel.getFlag();

	if (!channel.isOnChan(&user)) {
		sender.send(ResponseTypes::ERR_USERNOTINCHANNEL(user.getName().c_str(), channel.getName().c_str()));
		return ;
	}
		
	if (!modes) {
		string mod;
		string params;

		if (flags.anonymous)
			mod += 'a';
		if (flags.invite)
			mod += 'i';
		if (flags.moderate)
			mod += 'm';
		if (flags.outside_message)
			mod += 'n';
		if (flags.priv)
			mod += 'p';
		if (flags.reop)
			mod += 'r';
		if (flags.secret)
			mod += 's';
		if (flags.topic)
			mod += 't';
		if (!channel.getPassword().empty()) {
			mod += 'k';
			params += channel.getPassword() + ' ';
		}
		if (flags.user_limit) {
			mod += 'l';
			params += std::to_string(flags.user_limit);
		}
		sender.send(ResponseTypes::RPL_CHANNELMODEIS(channel.getName().c_str(), mod.c_str(), params.c_str()));
		return ;
	}
		
	if (!channel.isChanop(&user)) {
		sender.send(ResponseTypes::ERR_CHANOPRIVSNEEDED(channel.getName().c_str()));
		return ;
	}

	for (vector<Flag>::iterator i = modes->begin(); i != modes->end(); i++) {
		bool enabled = i->sign == '+';
		switch (i->letter) {
		case 'a': flags.anonymous = enabled; break;
		case 'i': flags.invite = enabled; break;
		case 'k':
			if (enabled && !channel.getPassword().empty())
				sender.send(ResponseTypes::ERR_KEYSET(channel.getName().c_str()));
			else if (enabled)
				channel.getPassword() = i->value;
			else
				channel.getPassword().clear();
			break;
		case 'l': 
			if (enabled)
				flags.user_limit = static_cast<int>(atoi(i->value.c_str()));
			else
				flags.user_limit = 0;
			break;
		case 'm': flags.moderate = enabled; break;
		case 'n': flags.outside_message = enabled; break;
		case 'o':
			if (enabled)
				channel.promoteChanop(irc.findUser(i->value));
			else
				channel.demoteChanop(irc.findUser(i->value));
			break;
		case 'p': flags.priv = enabled; break;
		case 'r': flags.reop = enabled; break;
		case 's': flags.secret = enabled; break;
		case 't': flags.topic = enabled; break;
		case 'v':
			if (enabled)
				channel.promoteVoiceOp(irc.findUser(i->value));
			else
				channel.demoteVoiceOp(irc.findUser(i->value));
			break;
		}
	}
}