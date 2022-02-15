#include "core/command/NickCommand.hpp"

void NickCommand::execute(const Command& cmd, CommandSender& sender) {
	User& user = dynamic_cast<User&>(sender);

	string& nickname = cmd.getArg<string>("nickname");
	if (nickname.empty() || nickname.find(' ') != string::npos) {
		user.send(ResponseTypes::ERR_ERRONEUSNICKNAME(nickname.c_str()));
		return;
	}
	bool wasRegistered = user.isRegistered();

	if (nickname == "anonymous" || Irc::getInstance().findUser(nickname)) {
		user.send(ResponseTypes::ERR_NICKNAMEINUSE());
		return;
	}
	user.setName(nickname);

	if (user.isRegistered() && !wasRegistered) {
		user.send(ResponseTypes::RPL_WELCOME(user.getName().c_str(), user.getUserName().c_str(), Irc::getInstance().getServer().getHost().c_str()));
		user.send(ResponseTypes::RPL_YOURHOST(Irc::getInstance().getServer().getName().c_str(), VERSION));
		user.send(ResponseTypes::RPL_CREATED(CREATION_DATE));
		user.send(ResponseTypes::RPL_MYINFO(Irc::getInstance().getServer().getName().c_str(), VERSION, "0", "0"));
	}
}