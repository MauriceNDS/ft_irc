#include "core/command/NickCommand.hpp"

#include "core/Irc.hpp"

#include "api/User.hpp"
#include "api/ResponseTypes.hpp"

void NickCommand::execute(const Command& cmd, CommandSender& sender) {
	User& user = dynamic_cast<User&>(sender);

	string& nickname = cmd.getArg<string>("nickname");
	if (!User::isValidName(nickname)) {
		user.send(ResponseTypes::ERR_ERRONEUSNICKNAME(user.getName().c_str(), nickname.c_str()));
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
