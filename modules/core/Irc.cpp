#include "core/Irc.hpp"
#include "core/command/TestCommand.hpp"
#include "core/command/UserCommand.hpp"
#include "core/command/NickCommand.hpp"

#include "core/command/elements/MsgToCommandElement.hpp"
#include "core/command/elements/UserCommandElement.hpp"
#include "core/command/elements/ChannelCommandElement.hpp"

#include "api/middleware/UserMiddleware.hpp"
#include "api/middleware/RegisteredUserMiddleware.hpp"

#include "api/command/CommandSpec.hpp"
#include "api/command/GenericArguments.hpp"

Irc::Irc(const string& name, const int port, const string& password, const vector<string>& plugins) : server(name, port, password) {
	Irc::instance = this;

	getPluginLoader().loadPlugins(plugins);

	for (map<const string, Plugin *>::const_iterator plugin = getPluginLoader().getPlugins().begin(); plugin != getPluginLoader().getPlugins().end(); plugin++)
		plugin->second->construct();

	for (map<const string, Plugin *>::const_iterator plugin = getPluginLoader().getPlugins().begin(); plugin != getPluginLoader().getPlugins().end(); plugin++)
		plugin->second->preInit();

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
		.name("JOIN")
		.argument("channels", GenericArguments::list<Channel>(new ChannelCommandElement(true)))
		.middleware(new RegisteredUserMiddleware())
		.executor(new TestCommand())
		.build()
	);
	commandManager.registerCommand(CommandSpec::Builder()
		.name("PART")
		.argument("channels", GenericArguments::list<Channel>(new ChannelCommandElement(false)))
		.argument("message", GenericArguments::optional(GenericArguments::string()))
		.middleware(new RegisteredUserMiddleware())
		.executor(new TestCommand())
		.build()
	);
	commandManager.registerCommand(CommandSpec::Builder()
		.name("KICK")
		.argument("channel", new ChannelCommandElement(false))
		.argument("user", new UserCommandElement())
		.argument("message", GenericArguments::optional(GenericArguments::string()))
		.middleware(new RegisteredUserMiddleware())
		.executor(new TestCommand())
		.build()
	);
	commandManager.registerCommand(CommandSpec::Builder()
		.name("TOPIC")
		.argument("channel", new ChannelCommandElement(false))
		.argument("topic", GenericArguments::optional(GenericArguments::string()))
		.middleware(new RegisteredUserMiddleware())
		.executor(new TestCommand())
		.build()
	);
	commandManager.registerCommand(CommandSpec::Builder()
		.name("PRIVMSG")
		.argument("msgtarget", GenericArguments::list<MsgToCommandElement *>(new MsgToCommandElement()))
		.argument("message", CommandElement::Builder()
			.element(GenericArguments::string())
			.ifNotProvided(ResponseTypes::ERR_NOTEXTTOSEND)
			.build())
		.middleware(new RegisteredUserMiddleware())
		.executor(new TestCommand())
		.build()
	);

	for (map<const string, Plugin *>::const_iterator plugin = getPluginLoader().getPlugins().begin(); plugin != getPluginLoader().getPlugins().end(); plugin++)
		plugin->second->init();

	for (map<const string, Plugin *>::const_iterator plugin = getPluginLoader().getPlugins().begin(); plugin != getPluginLoader().getPlugins().end(); plugin++)
		plugin->second->postInit();
}

void Irc::start() {
	for (map<const string, Plugin *>::const_iterator plugin = getPluginLoader().getPlugins().begin(); plugin != getPluginLoader().getPlugins().end(); plugin++)
		plugin->second->serverAboutToStart();

	server.start();
}

Irc::~Irc() {
	for (map<const string, Plugin *>::const_iterator plugin = getPluginLoader().getPlugins().begin(); plugin != getPluginLoader().getPlugins().end(); plugin++)
		plugin->second->serverStopping();

	for (vector<User *>::iterator i = users.begin(); i != users.end(); ++i)
		delete *i;

	users.clear();

	for (map<const string, Plugin *>::const_iterator plugin = getPluginLoader().getPlugins().begin(); plugin != getPluginLoader().getPlugins().end(); plugin++)
		plugin->second->serverStopped();
}

Irc *Irc::instance = NULL;
