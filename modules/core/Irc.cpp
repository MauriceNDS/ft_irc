#include "core/Irc.hpp"
#include "core/command/UserCommand.hpp"
#include "core/command/NickCommand.hpp"
#include "core/command/elements/UserCommandElement.hpp"

#include "api/command/CommandSpec.hpp"
#include "api/command/GenericArguments.hpp"

void Irc::start() {
	commandManager.registerCommand(CommandSpec::Builder()
		.name("USER")
		.argument("username", GenericArguments::string())
		.argument("mode", GenericArguments::string())
		.argument("unused", GenericArguments::string())
		.argument("realname", GenericArguments::string())
		.executor(new UserCommand())
		.build()
	);
	commandManager.registerCommand(CommandSpec::Builder()
		.name("NICK")
		.argument("nickname", GenericArguments::string())
		.executor(new NickCommand())
		.build()
	);

	server.listen();
	for (vector<User *>::iterator i = users.begin(); i != users.end(); ++i) {
		delete *i;
	}
}

Irc *Irc::instance = nullptr;
