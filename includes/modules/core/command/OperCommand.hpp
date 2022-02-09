#ifndef FT_IRC_CORE_OPER_COMMAND
#define FT_IRC_CORE_OPER_COMMAND

#include "ft_irc.hpp"

#include "core/Irc.hpp"

#include "api/User.hpp"
#include "api/command/CommandExecutor.hpp"

#include "api/ResponseTypes.hpp"

class OperCommand : public CommandExecutor {

	void execute(const Command& cmd, CommandSender& sender) {
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
};

#endif /* FT_IRC_CORE_OPER_COMMAND */
