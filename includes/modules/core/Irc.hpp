#ifndef FT_IRC_CORE
#define FT_IRC_CORE

#include "ft_irc.hpp"

#include "api/User.hpp"
#include "api/command/CommandManager.hpp"

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

	void start();

	CommandManager& getCommandManager() {
		return this->commandManager;
	}

	const CommandManager& getCommandManager() const {
		return this->commandManager;
	}

	User *findUser(const string& nickname) {
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

	~Irc();
};

#endif /* FT_IRC_CORE */
