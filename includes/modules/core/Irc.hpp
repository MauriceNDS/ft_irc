#ifndef FT_IRC_CORE
#define FT_IRC_CORE

#include "ft_irc.hpp"

#include "api/command/CommandManager.hpp"
#include "api/command/CommandSpec.hpp"
#include "api/command/GenericArguments.hpp"

#include "api/User.hpp"

#include "core/command/OperCommand.hpp"
#include "core/command/PartCommand.hpp"
#include "core/command/elements/UserCommandElement.hpp"

#include "server/Server.hpp"

class Channel {}; // #include "api/Channel.hpp"

class Irc {
private:
	static Irc *instance;

	Server server;
	CommandManager commandManager;

    vector<Channel *> channels;
    vector<User *> users;

public:
	static Irc& getInstance() {
		return *Irc::instance;
	}

	Irc(const string& name) : server(name) {
		Irc::instance = this;
	}

	void start() {
		commandManager.registerCommand(CommandSpec::Builder()
			.name("OPER")
			.argument("list", GenericArguments::list<User>(new UserCommandElement()))
			.argument("user", new UserCommandElement())
			.argument("action", GenericArguments::string())
			.argument("optional", GenericArguments::optional(new UserCommandElement()))
			.executor(new OperCommand())
			.build()
		);

		commandManager.registerCommand(CommandSpec::Builder()
			.name("PART")
			.argument("channels", GenericArguments::string())
			.argument("action", GenericArguments::string())
			.executor(new PartCommand())
			.build()
		);
		server.listen();
	}

	CommandManager& getCommandManager() {
		return this->commandManager;
	}

	const CommandManager& getCommandManager() const {
		return this->commandManager;
	}

	User *findUser(string& nickname) {
		for (vector<User *>::iterator it = users.begin(); it != users.end(); it++)
			if ((*it)->getNickName() == nickname)
				return *it;
		return NULL;
	}

	const vector<User *>& getUsers() const {
		return users;
	}

	void addUser(User *user) {
		users.push_back(user);
	}

	void removeUser(User *user) {
		for (vector<User *>::iterator it = users.begin(); it != users.end(); it++) {
			if (*it == user) {
				users.erase(it);
				break ;
			}
		}
	}

	// const vector<Channel *>& getChannels() const {
	// 	return channels;
	// }
};

#endif /* FT_IRC_CORE */
