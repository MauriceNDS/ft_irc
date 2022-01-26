#ifndef FT_IRC_CORE
#define FT_IRC_CORE

#include "ft_irc.hpp"

#include "api/User.hpp"
#include "api/Channel.hpp"
#include "api/command/CommandManager.hpp"

#include "server/Server.hpp"

#include "api/Channel.hpp"

class Irc {
private:
	static Irc *instance;

	Server server;
	CommandManager commandManager;

    map<string, Channel *> channels;
    vector<User *> users;
	set<User *> operators;

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

	Channel *findChannel(const string& channel) {
		map<string, Channel *>::iterator it = channels.find(channel);
		return it != channels.end() ? it->second : NULL;
	}

	void addChannel(Channel *channel) {
		channels[channel->getName()] = channel;
	}

	void removeChannel(Channel *channel) {
		channels.erase(channel->getName());
	}

	const map<string, Channel *>& getChannels() const {
	  	return channels;
	}

	void promoteOperator(User *user) {
		operators.insert(user);
	}
	void demoteOperator(User *user) {
		operators.erase(user);
	}

	bool isOperator(User *user) {
		return operators.find(user) != operators.end();
	}

	~Irc();
};

#endif /* FT_IRC_CORE */
