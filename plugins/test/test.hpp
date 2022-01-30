#ifndef FT_IRC_PLUGIN_TEST
#define FT_IRC_PLUGIN_TEST

#include "ft_irc.hpp"

#include "core/Irc.hpp"

#include "api/Plugin.hpp"
#include "api/command/CommandExecutor.hpp"

class MeuhCommand : public CommandExecutor {
public:
	void execute(const Command& cmd, CommandSender& sender);
};

class TestPlugin : public Plugin {
private:
	Irc *irc;

public:
	void construct();
	void init();
};

#endif /* FT_IRC_PLUGIN_TEST */
