#include "core/Irc.hpp"
#include "core/command/TestCommand.hpp"
#include "core/command/UserCommand.hpp"
#include "core/command/NickCommand.hpp"

#include "core/command/elements/MsgTargetCommandElement.hpp"
#include "core/command/elements/UserCommandElement.hpp"
#include "core/command/elements/ChannelCommandElement.hpp"

#include "api/middleware/UserMiddleware.hpp"
#include "api/middleware/RegisteredUserMiddleware.hpp"

#include "api/command/CommandSpec.hpp"
#include "api/command/GenericArguments.hpp"

void Irc::start() {
	commandManager.registerCommand(CommandSpec::Builder()
		.name("USER")
		.argument("user", GenericArguments::string())
		.argument("mode", GenericArguments::string())
		.argument("unused", GenericArguments::string())
		.argument("realname", GenericArguments::string())
		.middleware(new UserMiddleware())
		.executor(new UserCommand())
		.build()
	);
	commandManager.registerCommand(CommandSpec::Builder()
		.name("NICK")
		.argument("nickname", CommandElement::Builder()
			.element(GenericArguments::string())
			.ifNotProvided(ResponseTypes::ERR_NONICKNAMEGIVEN)
			.build())
		.middleware(new UserMiddleware())
		.executor(new NickCommand())
		.build()
	);
	commandManager.registerCommand(CommandSpec::Builder()
		.name("PRIVMSG")
		.argument("msgtarget", new MsgTargetCommandElement())
		.argument("message", CommandElement::Builder()
			.element(GenericArguments::string())
			.ifNotProvided(ResponseTypes::ERR_NOTEXTTOSEND)
			.build())
		.middleware(new RegisteredUserMiddleware())
		.executor(new TestCommand())
		.build()
	);
	commandManager.registerCommand(CommandSpec::Builder()
		.name("JOIN")
		.argument("channels", GenericArguments::list<Channel>(new ChannelCommandElement(true)))
		.middleware(new RegisteredUserMiddleware())
		.executor(new TestCommand())
		.build()
	);
	commandManager.registerCommand(CommandSpec::Builder()
		.name("PART")
		.argument("channels", GenericArguments::list<Channel>(new ChannelCommandElement(false)))
		.argument("realname", GenericArguments::string())
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

Irc *Irc::instance = NULL;
