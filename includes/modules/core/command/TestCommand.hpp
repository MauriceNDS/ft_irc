#ifndef FT_IRC_CORE_TEST_COMMAND
#define FT_IRC_CORE_TEST_COMMAND

#include "ft_irc.hpp"

#include "api/command/CommandExecutor.hpp"

#include "server/Response.hpp"

class TestCommand : public CommandExecutor {

	Response execute(const Command& cmd, Client& sender) {
		(void)cmd;
		(void)sender;
		std::cout << "(test)" << std::endl;
		return RPL_NONE;
	}
};

#endif /* FT_IRC_CORE_TEST_COMMAND */
