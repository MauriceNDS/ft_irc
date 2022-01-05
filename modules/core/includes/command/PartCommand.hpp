#ifndef FT_IRC_CORE_PART_COMMAND
#define FT_IRC_CORE_PART_COMMAND

#include "ft_irc.hpp"

#include "core/includes/interface/User.hpp"

#include "server/includes/Response.hpp"
#include "commands/includes/CommandSender.hpp"
#include "commands/includes/CommandExecutor.hpp"

class PartCommand : public CommandExecutor {

	Response execute(Command cmd, CommandSender sender) {
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
