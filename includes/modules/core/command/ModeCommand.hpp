#ifndef FT_IRC_CORE_MODE_COMMAND
#define FT_IRC_CORE_MODE_COMMAND

#include "ft_irc.hpp"

#include "core/Irc.hpp"

#include "api/ResponseTypes.hpp"
#include "api/User.hpp"
#include "api/command/CommandExecutor.hpp"

#include "api/ResponseTypes.hpp"

class ModeCommand : public CommandExecutor {

	void execute(const Command& cmd, CommandSender& sender) {
		User& user = static_cast<User&>(sender);

		Channel& channel = cmd.getArg<Channel>("channel");
		string *mode = cmd.getArg<string *>("mode");
		vector<string *> *modeparams = cmd.getArg<vector<string *> *>("modeparams");

		int sign = 0;
		size_t param_i = 0;
		Irc& server = Irc::getInstance();
		flag &flags = channel.getFlag();

		if (mode && !channel.isChanop(&user)) {
			sender.send(ResponseTypes::ERR_CHANOPRIVSNEEDED(channel.getName().c_str()));
			return ;
		} else if (!channel.isOnChan(&user)) {
			sender.send(ResponseTypes::ERR_USERNOTINCHANNEL(user.getName().c_str(), channel.getName().c_str()));
			return ;
		} else if (!mode) {
			string mod;
			string params;

			if (flags.anonymous) {
				mod += "a";
			} if (flags.invite) {
				mod += "i";
			} if (flags.moderate) {
				mod += "m";
			} if (flags.outside_message) {
				mod += "n";
			} if (flags.quiet) {
				mod += "q";
			} if (flags.priv) {
				mod += "p";
			} if (flags.secret) {
				mod += "s";
			} if (flags.reop) {
				mod += "r";
			} if (flags.topic) {
				mod += "t";
			} if (!channel.getPassword().empty()) {
				mod += "i";
				params += channel.getPassword() + " ";
			} if (flags.user_limit) {
				mod += "i";
				params += std::to_string(flags.user_limit);
			}
			sender.send(ResponseTypes::RPL_CHANNELMODEIS(channel.getName().c_str(), mod.c_str(), params.c_str()));
			return ;
		}

		if ((*mode)[0] == '+') {
			sign = 1;
		} else if ((*mode)[0] == '-') {
			sign = 2;
		}

		for (size_t i = sign ? 1 : 0; i < mode->size(); i++) {
			if ((*mode)[i] == 'o') {
				if (!modeparams || param_i > (*modeparams).size()) {
					sender.send(ResponseTypes::ERR_NEEDMOREPARAMS());
				} else if (sign == 1) {
					channel.promoteChanop(server.findUser(*((*modeparams)[param_i])));
				} else if (sign == 2){
					channel.demoteChanop(server.findUser(*((*modeparams)[param_i])));
				}
				param_i++;
			} else if ((*mode)[i] == 'v') {
				if (!modeparams || param_i > (*modeparams).size()) {
					sender.send(ResponseTypes::ERR_NEEDMOREPARAMS());
				} else if (sign == 1) {
					channel.promoteVoiceOp(server.findUser(*((*modeparams)[param_i])));
				} else if (sign == 2){
					channel.demoteVoiceOp(server.findUser(*((*modeparams)[param_i])));
				}
				param_i++;
			} else if ((*mode)[i] == 'a') {
				flags.anonymous = flags.anonymous ? 0 : 1;
			} else if ((*mode)[i] == 'i') {
				flags.invite = flags.invite ? 0 : 1;
			} else if ((*mode)[i] == 'm') {
				flags.moderate = flags.moderate ? 0 : 1;
			} else if ((*mode)[i] == 'n') {
				flags.outside_message = flags.outside_message ? 0 : 1;
			} else if ((*mode)[i] == 'q') {
				flags.quiet = flags.quiet ? 0 : 1;
			} else if ((*mode)[i] == 'p') {
				flags.priv = flags.priv ? 0 : 1;
			} else if ((*mode)[i] == 's') {
				flags.secret = flags.secret ? 0 : 1;
			} else if ((*mode)[i] == 'r') {
				flags.reop = flags.reop ? 0 : 1;
			} else if ((*mode)[i] == 't') {
				flags.topic = flags.topic ? 0 : 1;
			} else if ((*mode)[i] == 'k') {
				if ((!modeparams || param_i > (*modeparams).size()) && sign == 1) {
					sender.send(ResponseTypes::ERR_NEEDMOREPARAMS());
				} else if (sign == 1 && !channel.getPassword().empty()) {
					sender.send(ResponseTypes::ERR_KEYSET(channel.getName().c_str()));
				} else if (sign == 1) {
					channel.getPassword() = *((*modeparams)[param_i]);
				} else if (sign == 2){
					channel.getPassword().clear();
				}
				param_i++;
			} else if ((*mode)[i] == 'l') {
				if ((!modeparams || param_i > (*modeparams).size()) && sign == 1) {
					sender.send(ResponseTypes::ERR_NEEDMOREPARAMS());
				} else if (sign == 1) {
					flags.user_limit = atoi((*((*modeparams)[param_i])).c_str());
				} else if (sign == 2){
					flags.user_limit = 0;
				}
				param_i++;
			} else {
				sender.send(ResponseTypes::ERR_UNKNOWNMODE(&(*mode)[i], channel.getName().c_str()));
			}
		}
	}
};


#endif /* FT_IRC_CORE_MODE_COMMAND */