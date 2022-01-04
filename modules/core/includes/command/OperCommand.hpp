#ifndef FT_IRC_CORE_OPER_COMMAND
#define FT_IRC_CORE_OPER_COMMAND

#include "ft_irc.hpp"

#include "core/includes/interface/User.hpp"

#include "core/includes/server/Response.hpp"
#include "parsing/includes/CommandSender.hpp"
#include "parsing/includes/CommandExecutor.hpp"

// TODO test
#include <iostream>

class OperCommand : public CommandExecutor {

	Response execute(Command cmd, CommandSender sender) {
		(void)sender;
		std::cout << "==== OPER ====" << std::endl;

		User& user = cmd.getArg<User>("user");
		string& action = cmd.getArg<string>("action");
		User*& optional = cmd.getArg<User*>("optional");

		std::cout << user.getName() << std::endl;
		std::cout << "---" << std::endl;
		std::cout << action << std::endl;
		std::cout << "---" << std::endl;
		if (optional)
			std::cout << "Optional user found" << std::endl;
		else
			std::cout << "Optional user not found" << std::endl;

		return NONE;
	}
};

#endif /* FT_IRC_CORE_OPER_COMMAND */
