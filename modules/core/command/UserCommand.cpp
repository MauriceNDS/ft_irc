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
		user.send(ResponseTypes::RPL_WELCOME(user.getName().c_str(), user.getUserName().c_str(), Irc::getInstance().getServer().getHost().c_str()));
		user.send(ResponseTypes::RPL_YOURHOST(Irc::getInstance().getServer().getName().c_str(), VERSION));
		user.send(ResponseTypes::RPL_CREATED(CREATION_DATE));
		user.send(ResponseTypes::RPL_MYINFO(Irc::getInstance().getServer().getName().c_str(), VERSION, "0", "0"));
	}
}
