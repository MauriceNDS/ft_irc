#include "core/command/ModeCommand.hpp"

#include "core/Irc.hpp"

#include "api/Flag.hpp"
#include "api/User.hpp"
#include "api/Channel.hpp"

#include "api/ResponseTypes.hpp"

static void concat_mode_rpl(string & mode_output, vector<Flag>::iterator & i) {
	if (!mode_output.empty())
			mode_output += " ";
		mode_output.push_back(i->sign);
		mode_output.push_back(i->letter);
		if (!i->value.empty()) {
			mode_output.append(" ");
			mode_output.append(i->value);
		}
}

void ModeCommand::execute(const Command& cmd, CommandSender& sender) {
	User& user = static_cast<User&>(sender);
	Channel& channel = cmd.getArg<Channel>("channel");
	vector<Flag> *modes = cmd.getArg<vector<Flag> *>("mode");

	Irc& irc = Irc::getInstance();
	Modes &flags = channel.getFlags();

	if (!channel.containsUser(user)) {
		sender.send(ResponseTypes::ERR_USERNOTINCHANNEL(user.getName().c_str(), channel.getName().c_str()));
		return ;
	}
		
	if (!modes) {
		string mod;
		string params;

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
			params += ::itos(flags.user_limit);
		}
		sender.send(ResponseTypes::RPL_CHANNELMODEIS(sender.getName().c_str(), channel.getName().c_str(), mod.c_str(), params.c_str()));
		return ;
	}
		
	if (!channel.isOperator(user)) {
		sender.send(ResponseTypes::ERR_CHANOPRIVSNEEDED(channel.getName().c_str()));
		return ;
	}

	string mode_output;
	User *target;

	for (vector<Flag>::iterator i = modes->begin(); i != modes->end(); i++) {
		bool enabled = i->sign == '+';
		switch (i->letter) {
		case 'i': flags.invite = enabled; break;
		case 'k':
			if (enabled && !channel.getPassword().empty())
				sender.send(ResponseTypes::ERR_KEYSET(channel.getName().c_str()));
			else if (enabled)
				channel.setPassword(i->value);
			else
				channel.setPassword("");
			break;
		case 'l': 
			if (enabled)
				flags.user_limit = atoi(i->value.c_str());
			else
				flags.user_limit = 0;
			break;
		case 'm': flags.moderate = enabled; break;
		case 'n': flags.outside_message = enabled; break;
		case 'o':
			target = irc.findUser(i->value);
			if (!target)
				break;
			if (enabled)
				channel.promote(*target);
			else
				channel.demote(*target);
			break;
		case 'p': flags.priv = enabled; break;
		case 'r': flags.reop = enabled; break;
		case 's': flags.secret = enabled; break;
		case 't': flags.topic = enabled; break;
		case 'v':
			target = irc.findUser(i->value);
			if (!target)
				break;
			if (enabled)
				channel.promoteVoiceOp(*target);
			else
				channel.demoteVoiceOp(*target);
			break;
		}
		concat_mode_rpl(mode_output, i);
	}
	channel.send(ResponseTypes::MODE(user, channel.getName().c_str(), mode_output.c_str()));
}
