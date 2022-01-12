#ifndef FT_IRC_CORE_OPER_COMMAND
#define FT_IRC_CORE_OPER_COMMAND

#include "ft_irc.hpp"

#include "api/User.hpp"
#include "api/command/CommandExecutor.hpp"

#include "server/Response.hpp"

class OperCommand : public CommandExecutor {
public:
	Response execute(const Command& cmd, User *sender) {
		std::cout << "=== OPER ===" << std::endl;

		vector<User*>& users = cmd.getArg<vector<User*> >("list");
		string& action = cmd.getArg<string>("action");
		User*& optional = cmd.getArg<User*>("optional");

		(void)sender;
		(void)users;
		(void)action;
		(void)optional;
		return NONE;
	}
};

#endif /* FT_IRC_CORE_OPER_COMMAND */
