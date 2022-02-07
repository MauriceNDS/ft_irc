#include "core/Irc.hpp"
#include "core/command/TestCommand.hpp"
#include "core/command/UserCommand.hpp"
#include "core/command/NickCommand.hpp"
#include "core/command/JoinCommand.hpp"
#include "core/command/KickCommand.hpp"
#include "core/command/NoticeCommand.hpp"
#include "core/command/OperCommand.hpp"
#include "core/command/PartCommand.hpp"
#include "core/command/PingCommand.hpp"
#include "core/command/PrivmsgCommand.hpp"
#include "core/command/TopicCommand.hpp"
#include "core/command/PassCommand.hpp"

#include "core/command/elements/MsgToCommandElement.hpp"
#include "core/command/elements/UserCommandElement.hpp"
#include "core/command/elements/ChannelCommandElement.hpp"

#include "api/middleware/UserMiddleware.hpp"
#include "api/middleware/RegisteredUserMiddleware.hpp"
#include "api/middleware/ValidPassMiddleware.hpp"

#include "api/command/CommandSpec.hpp"
#include "api/command/GenericArguments.hpp"

void Irc::start() {
	commandManager.registerCommand(CommandSpec::Builder()
		.name("USER")
		.argument("user", GenericArguments::string())
		.argument("mode", GenericArguments::string())
		.argument("unused", GenericArguments::string())
		.argument("realname", GenericArguments::string())
		.middleware(new ValidPassMiddleware())
		.executor(new UserCommand())
		.build()
	);
	commandManager.registerCommand(CommandSpec::Builder()
		.name("NICK")
		.argument("nickname", CommandElement::Builder()
			.element(GenericArguments::string())
			.ifNotProvided(ResponseTypes::ERR_NONICKNAMEGIVEN)
			.build())
		.middleware(new ValidPassMiddleware())
		.executor(new NickCommand())
		.build()
	);
	commandManager.registerCommand(CommandSpec::Builder()
		.name("JOIN")
		.argument("channels", GenericArguments::list<Channel>(new ChannelCommandElement(true)))
		.middleware(new RegisteredUserMiddleware())
		.executor(new JoinCommand())
		.build()
	);
	commandManager.registerCommand(CommandSpec::Builder()
		.name("PART")
		.argument("channels", GenericArguments::list<Channel>(new ChannelCommandElement(false)))
		.argument("message", GenericArguments::optional(GenericArguments::string()))
		.middleware(new RegisteredUserMiddleware())
		.executor(new PartCommand())
		.build()
	);
	commandManager.registerCommand(CommandSpec::Builder()
		.name("KICK")
		.argument("channel", new ChannelCommandElement(false))
		.argument("user", new UserCommandElement())
		.argument("message", GenericArguments::optional(GenericArguments::string()))
		.middleware(new RegisteredUserMiddleware())
		.executor(new KickCommand())
		.build()
	);
	commandManager.registerCommand(CommandSpec::Builder()
		.name("TOPIC")
		.argument("channel", new ChannelCommandElement(false))
		.argument("topic", GenericArguments::optional(GenericArguments::string()))
		.middleware(new RegisteredUserMiddleware())
		.executor(new TopicCommand())
		.build()
	);
	commandManager.registerCommand(CommandSpec::Builder()
		.name("PRIVMSG")
		.argument("msgtarget", GenericArguments::list<MsgToCommandElement>(new MsgToCommandElement()))
		.argument("message", CommandElement::Builder()
			.element(GenericArguments::string())
			.ifNotProvided(ResponseTypes::ERR_NOTEXTTOSEND)
			.build())
		.middleware(new RegisteredUserMiddleware())
		.executor(new PrivmsgCommand())
		.build()
	);
	commandManager.registerCommand(CommandSpec::Builder()
		.name("NOTICE")
		.argument("msgtarget", GenericArguments::list<MsgToCommandElement>(new MsgToCommandElement()))
		.argument("message", GenericArguments::string())
		.middleware(new RegisteredUserMiddleware())
		.executor(new NoticeCommand())
		.build()
	);
	commandManager.registerCommand(CommandSpec::Builder()
		.name("PING")
		.argument("server", CommandElement::Builder()
			.element(GenericArguments::string())
			.ifNotProvided(ResponseTypes::ERR_NOORIGIN)
			.build())
		.middleware(new RegisteredUserMiddleware())
		.executor(new PingCommand())
		.build()
	);
	commandManager.registerCommand(CommandSpec::Builder()
		.name("OPER")
		.argument("name", GenericArguments::string())
		.argument("password", GenericArguments::string())
		.middleware(new RegisteredUserMiddleware())
		.executor(new OperCommand())
		.build()
	);
	commandManager.registerCommand(CommandSpec::Builder()
		.name("PASS")
		.argument("password", GenericArguments::string())
		.middleware(new UserMiddleware())
		.executor(new PassCommand())
		.build()
	);

	server.start();
}

Irc::~Irc() {
	for (vector<User *>::iterator i = users.begin(); i != users.end(); ++i) {
		delete *i;
	}
}

Irc *Irc::instance = NULL;
