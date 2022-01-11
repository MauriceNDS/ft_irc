#ifndef FT_IRC_CORE_PART_COMMAND
#define FT_IRC_CORE_PART_COMMAND

#include "ft_irc.hpp"

#include "api/User.hpp"
#include "server/Response.hpp"
#include "api/command/CommandExecutor.hpp"

class PartCommand : public CommandExecutor {
public:
	Response execute(const Command& cmd, User *sender) {
		std::cout << "=== PART ===" << std::endl;

		string& user = cmd.getArg<string>("channels");
		string& action = cmd.getArg<string>("action");

		(void)sender;
		(void)user;
		(void)action;
		return NONE;
	}
};

#endif /* FT_IRC_CORE_PART_COMMAND */
