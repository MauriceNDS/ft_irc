#include "core/command/OperCommand.hpp"

void OperCommand::execute(const Command& cmd, CommandSender& sender) {
	const string test_name = "operator";
	const string test_password = "1234";

	string& name = cmd.getArg<string>("name");
	string& password = cmd.getArg<string>("password");

	if (name != test_name) {
		sender.send(ResponseTypes::ERR_NOOPERHOST().c_str());
	} else if (password != test_password) {
		sender.send(ResponseTypes::ERR_PASSWDMISMATCH().c_str());
	} else if (!Irc::getInstance().isOperator(static_cast<User *>(&sender))){
		sender.send(ResponseTypes::RPL_YOUREOPER());
		Irc::getInstance().promoteOperator(&static_cast<User &>(sender));
	}
}