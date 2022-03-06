#include "core/command/OperCommand.hpp"

#include "core/Irc.hpp"

#include "api/User.hpp"
#include "api/ResponseTypes.hpp"

void OperCommand::execute(const Command& cmd, CommandSender& sender) {
	User &user = static_cast<User &>(sender);
	const string test_name = "operator";
	const string test_password = "1234";

	string& name = cmd.getArg<string>("name");
	string& password = cmd.getArg<string>("password");

	if (name != test_name) {
		sender.send(ResponseTypes::ERR_NOOPERHOST(user.getName().c_str()).c_str());
	} else if (password != test_password) {
		sender.send(ResponseTypes::ERR_PASSWDMISMATCH(user.getName().c_str()).c_str());
	} else if (!Irc::getInstance().isOperator(user)){
		sender.send(ResponseTypes::RPL_YOUREOPER(user.getName().c_str()));
		Irc::getInstance().promote(user);
	}
}
