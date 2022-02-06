#include "plugin.hpp"

#include "api/ResponseTypes.hpp"

PLUGIN(TestPlugin)

void TestPlugin::construct() {
	irc = &Irc::getInstance();
}

void TestPlugin::init() {
	irc->getCommandManager().registerCommand(CommandSpec::Builder()
		.name("TEST")
		.executor(new MeuhCommand())
		.build()
	);
}

void MeuhCommand::execute(const Command& cmd, CommandSender& sender) {
	(void)cmd;
	sender.send("meuh\n");
}
