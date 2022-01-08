#ifndef FT_IRC_CORE_PART_COMMAND
#define FT_IRC_CORE_PART_COMMAND

#include "ft_irc.hpp"

#include "core/interface/User.hpp"

#include "server/Response.hpp"
#include "commands/CommandSender.hpp"
#include "commands/CommandExecutor.hpp"

class PartCommand : public CommandExecutor {

	Response execute(const Command& cmd, CommandSender& sender) {
		(void)sender;
		std::cout << "==== PART ====" << std::endl;

		string& user = cmd.getArg<string>("channels");
		string& action = cmd.getArg<string>("action");

		std::cout << user << std::endl;
		std::cout << "---" << std::endl;
		std::cout << action << std::endl;

		return NONE;
	}
};

#endif /* FT_IRC_CORE_PART_COMMAND */
