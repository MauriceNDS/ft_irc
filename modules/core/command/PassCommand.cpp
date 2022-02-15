#include "core/command/PassCommand.hpp"

void PassCommand::execute(const Command& cmd, CommandSender& sender) {
	User& user = static_cast<User &>(sender);

	string& password = cmd.getArg<string>("password");
	if (user.isRegistered()) {
		user.send(ResponseTypes::ERR_ALREADYREGISTRED());
	} else if (Irc::getInstance().getServer().getPassword() != password) {
		Client& client = static_cast<Client &>(sender);
		client.getConnection()->closeConnection = true;
	} else {
		user.setValidPassword(true);
	}
}
