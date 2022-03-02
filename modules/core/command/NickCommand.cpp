#include "core/command/NickCommand.hpp"

#include "core/Irc.hpp"

#include "api/User.hpp"
#include "api/ResponseTypes.hpp"

void NickCommand::execute(const Command& cmd, CommandSender& sender) {
	User& user = dynamic_cast<User&>(sender);

	string& nickname = cmd.getArg<string>("nickname");
	if (nickname.empty() || nickname.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_") != string::npos) {
		user.send(ResponseTypes::ERR_ERRONEUSNICKNAME(nickname.c_str()));
		return;
	}
	bool wasRegistered = user.isRegistered();

	if (nickname == "anonymous" || Irc::getInstance().findUser(nickname)) {
		user.send(ResponseTypes::ERR_NICKNAMEINUSE(nickname.c_str()));
		return;
	}
	if (user.isRegistered())
		Irc::getInstance().broadcast(ResponseTypes::NICK(user, nickname.c_str()));
	user.setName(nickname);

	if (user.isRegistered() && !wasRegistered)
		Irc::getInstance().sendWelcomeMessage(user);
}
