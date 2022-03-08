#include "core/command/UserCommand.hpp"

#include "core/Irc.hpp"

#include "api/User.hpp"
#include "api/ResponseTypes.hpp"

void UserCommand::execute(const Command& cmd, CommandSender& sender) {
	User& user = dynamic_cast<User&>(sender);

	if (!(user.getUserName().empty())) {
		user.send(ResponseTypes::ERR_ALREADYREGISTRED());
		return;
	}

	user.setUserName(cmd.getArg<string>("user"));
	user.setRealName(cmd.getArg<string>("realname"));

	if (user.isRegistered()) {
		std::cout << "[INFO] " << user.getName() << " registered" << std::endl;
		Irc::getInstance().sendWelcomeMessage(user);
	}
}
