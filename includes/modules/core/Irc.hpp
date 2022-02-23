#ifndef FT_IRC_CORE
#define FT_IRC_CORE

#include "ft_irc.hpp"

#include "api/PluginLoader.hpp"
#include "api/command/CommandManager.hpp"

#include "server/Server.hpp"

#define CREATION_DATE "28/01/2022"
#define VERSION "1.0"

class User;
class Channel;

class Irc {
private:
	static Irc *instance;

	Server server;
	CommandManager commandManager;
	PluginLoader pluginLoader;

    map<string, Channel *> channels;
    vector<User *> users;
	set<User *> operators;

public:
	static Irc& getInstance();

	Irc(const string& name, const int port, const string& password, const vector<string>& plugins);

	void start();

	CommandManager& getCommandManager();
	PluginLoader& getPluginLoader();
	const CommandManager& getCommandManager() const;
	const PluginLoader& getPluginLoader() const;

	const vector<User *>& getUsers() const;
	User *findUser(const string& nickname);
	void addUser(User *user);
	void removeUser(User *user);

	const map<string, Channel *>& getChannels() const;
	Channel *findChannel(const string& channel);
	void addChannel(Channel *channel);
	void removeChannel(Channel *channel);

	void promoteOperator(User *user);
	void demoteOperator(User *user);
	bool isOperator(User *user);

	const Server& getServer() const;

	void sendWelcomeMessage(User& user);

	~Irc();
};

#endif /* FT_IRC_CORE */
