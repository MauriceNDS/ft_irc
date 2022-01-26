#ifndef FT_IRC_CORE_TEST_COMMAND
#define FT_IRC_CORE_TEST_COMMAND

#include "ft_irc.hpp"

#include "api/command/CommandExecutor.hpp"

#include "api/ResponseTypes.hpp"

class TestCommand : public CommandExecutor {

	void execute(const Command& cmd, CommandSender& sender) {
		(void)cmd;
		(void)sender;
	}
};

#endif /* FT_IRC_CORE_TEST_COMMAND */
