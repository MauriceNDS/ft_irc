#include "core/Irc.hpp"
#include "core/command/TestCommand.hpp"
#include "core/command/UserCommand.hpp"
#include "core/command/NickCommand.hpp"
#include "core/command/elements/UserCommandElement.hpp"

#include "api/middleware/UserMiddleware.hpp"
#include "api/middleware/RegisteredUserMiddleware.hpp"

#include "api/command/CommandSpec.hpp"
#include "api/command/GenericArguments.hpp"

void Irc::start() {
	commandManager.registerCommand(CommandSpec::Builder()
		.name("USER")
		.argument("username", GenericArguments::string())
		.argument("mode", GenericArguments::string())
		.argument("unused", GenericArguments::string())
		.argument("realname", GenericArguments::string())
		.middleware(new UserMiddleware())
		.executor(new UserCommand())
		.build()
	);
	commandManager.registerCommand(CommandSpec::Builder()
		.name("NICK")
		.argument("nickname", GenericArguments::string())
		.middleware(new UserMiddleware())
		.executor(new NickCommand())
		.build()
	);
	commandManager.registerCommand(CommandSpec::Builder()
		.name("TEST")
		.middleware(new RegisteredUserMiddleware())
		.executor(new TestCommand())
		.build()
	);

	server.listen();
}

Irc::~Irc() {
	for (vector<User *>::iterator i = users.begin(); i != users.end(); ++i) {
		delete *i;
	}
}

Irc *Irc::instance = nullptr;
