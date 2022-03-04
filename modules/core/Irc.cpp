#include "core/Irc.hpp"
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
#include "core/command/NamesCommand.hpp"
#include "core/command/InviteCommand.hpp"
#include "core/command/ListCommand.hpp"
#include "core/command/QuitCommand.hpp"
#include "core/command/ModeCommand.hpp"

#include "core/command/element/MsgToCommandElement.hpp"
#include "core/command/element/UserCommandElement.hpp"
#include "core/command/element/ChannelCommandElement.hpp"

#include "api/User.hpp"
#include "api/Channel.hpp"

#include "api/middleware/UserMiddleware.hpp"
#include "api/middleware/RegisteredUserMiddleware.hpp"
#include "api/middleware/ValidPassMiddleware.hpp"

#include "api/command/CommandSpec.hpp"
#include "api/command/GenericArguments.hpp"

#include "api/command/element/FlagsCommandElement.hpp"

Irc& Irc::getInstance() {
	return *Irc::instance;
}

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
		.argument("keys", GenericArguments::optional(GenericArguments::list<string>(GenericArguments::string())))
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
	commandManager.registerCommand(CommandSpec::Builder()
		.name("NAMES")
		.argument("channels", GenericArguments::optional(GenericArguments::list<Channel>(new ChannelCommandElement(true))))
		.middleware(new RegisteredUserMiddleware())
		.executor(new NamesCommand())
		.build()
	);
	commandManager.registerCommand(CommandSpec::Builder()
		.name("LIST")
		.argument("channels", GenericArguments::optional(GenericArguments::list<Channel>(new ChannelCommandElement(true))))
		.middleware(new RegisteredUserMiddleware())
		.executor(new ListCommand())
		.build()
	);
	commandManager.registerCommand(CommandSpec::Builder()
		.name("INVITE")
		.argument("nickname", new UserCommandElement())
		.argument("channel", GenericArguments::string())
		.middleware(new RegisteredUserMiddleware())
		.executor(new InviteCommand())
		.build()
	);
	commandManager.registerCommand(CommandSpec::Builder()
		.name("QUIT")
		.argument("message", GenericArguments::optional(GenericArguments::string()))
		.middleware(new RegisteredUserMiddleware())
		.executor(new QuitCommand())
		.build()
	);
	commandManager.registerCommand(CommandSpec::Builder()
		.name("MODE")
		.argument("channel", new ChannelCommandElement(false))
		.argument("mode", GenericArguments::optional(new FlagsCommandElement("o:v:aimnpsrtk+l+")))
		.middleware(new RegisteredUserMiddleware())
		.executor(new ModeCommand())
		.build()
	);

	for (map<const string, Plugin *>::const_iterator plugin = getPluginLoader().getPlugins().begin(); plugin != getPluginLoader().getPlugins().end(); plugin++)
		plugin->second->init();

	for (map<const string, Plugin *>::const_iterator plugin = getPluginLoader().getPlugins().begin(); plugin != getPluginLoader().getPlugins().end(); plugin++)
		plugin->second->postInit();
}

CommandManager& Irc::getCommandManager() {
	return this->commandManager;
}

PluginLoader& Irc::getPluginLoader() {
	return this->pluginLoader;
}

const CommandManager& Irc::getCommandManager() const {
	return this->commandManager;
}

const PluginLoader& Irc::getPluginLoader() const {
	return this->pluginLoader;
}

void Irc::start() {
	for (map<const string, Plugin *>::const_iterator plugin = getPluginLoader().getPlugins().begin(); plugin != getPluginLoader().getPlugins().end(); plugin++)
		plugin->second->serverAboutToStart();

	server.start();
}

void Irc::broadcast(const string& message) const {
	for (vector<User *>::const_iterator it = users.begin(); it != users.end(); it++) {
		(*it)->send(message);
	}
}

User *Irc::findUser(const string& nickname) const {
	for (vector<User *>::const_iterator it = users.begin(); it != users.end(); it++) {
		User *user = *it;
		if (nickname == user->getName())
			return *it;
	}
	return NULL;
}

const vector<User *>& Irc::getUsers() const {
	return users;
}

void Irc::addUser(User *user) {
	users.push_back(user);
}

void Irc::removeUser(User *user) {
	for (vector<User *>::iterator it = users.begin(); it != users.end(); it++) {
		if (*it == user) {
			users.erase(it);
			break ;
		}
	}
}

Channel *Irc::findChannel(const string& channel) const {
	map<string, Channel *>::const_iterator it = channels.find(channel);
	return it != channels.end() ? it->second : NULL;
}

void Irc::addChannel(Channel *channel) {
	if (channel)
		channels.insert(make_pair(channel->getName(), channel));
}

void Irc::removeChannel(Channel *channel) {
	channels.erase(channel->getName());
}

const map<string, Channel *>& Irc::getChannels() const {
	return channels;
}

void Irc::promoteOperator(User *user) {
	operators.insert(user);
}

void Irc::demoteOperator(User *user) {
	operators.erase(user);
}

bool Irc::isOperator(User *user) {
	return operators.find(user) != operators.end();
}

const Server& Irc::getServer() const {
	return server;
}

void Irc::sendWelcomeMessage(User& user) {
	user.send(ResponseTypes::RPL_WELCOME(user.getName().c_str(), user.getSenderName().c_str()));
	user.send(ResponseTypes::RPL_YOURHOST(user.getName().c_str(), Irc::getInstance().getServer().getName().c_str(), VERSION));
	user.send(ResponseTypes::RPL_CREATED(user.getName().c_str(), CREATION_DATE));
	user.send(ResponseTypes::RPL_MYINFO(user.getName().c_str(), Irc::getInstance().getServer().getName().c_str(), VERSION, "0", "0"));
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
