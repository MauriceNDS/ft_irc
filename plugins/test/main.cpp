#include "test.hpp"

#include "api/ResponseTypes.hpp"

PLUGIN(TestPlugin)

void TestPlugin::onStart(Irc& irc) {
	irc.getCommandManager().registerCommand(CommandSpec::Builder()
		.name("TEST")
		.executor(new MeuhCommand())
		.build()
	);
}

void TestPlugin::onStop() {}

void MeuhCommand::execute(const Command& cmd, CommandSender& sender) {
	(void)cmd;
	sender.send("meuh\n");
}
