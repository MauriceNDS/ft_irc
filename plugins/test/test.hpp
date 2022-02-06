#ifndef TEST_HPP
#define TEST_HPP

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

#endif /* TEST_HPP */
