#ifndef FT_IRC_CORE_TEST_COMMAND
#define FT_IRC_CORE_TEST_COMMAND

#include "ft_irc.hpp"

#include "api/command/CommandExecutor.hpp"

#include "api/ResponseType.hpp"

class TestCommand : public CommandExecutor {

	ResponseType execute(const Command& cmd, CommandSender& sender) {
		(void)cmd;
		(void)sender;
		return RPL_NONE;
	}
};

#endif /* FT_IRC_CORE_TEST_COMMAND */
