#ifndef FT_IRC_CORE
#define FT_IRC_CORE

#include "ft_irc.hpp"

#include "api/Group.hpp"
#include "api/PluginLoader.hpp"
#include "api/command/CommandManager.hpp"

#include "server/Server.hpp"

#define CREATION_DATE "28/01/2022"
#define VERSION "1.0"

class User;
class Channel;

class Irc : public Group {
private:
	static Irc *instance;

	PluginLoader pluginLoader;
	Server server;
	CommandManager commandManager;

public:
	static Irc& getInstance();

	Irc(const string& name, const int port, const string& password, const vector<string>& plugins);
	~Irc();

	// Server
	const Server& getServer() const;
	void start();

	// PluginLoader
	PluginLoader& getPluginLoader();
	const PluginLoader& getPluginLoader() const;

	// CommandManager
	CommandManager& getCommandManager();
	const CommandManager& getCommandManager() const;

	// Channels
	/**
	 * @brief Provide a filtered view of getChilds with channels only.
	 */
	map<string, Channel *> getChannels() const;
	Channel *findChannel(const string& channel) const;

	// Server
	Server& getServer();

	// Misc
	void broadcast(const string& message) const;
	void sendWelcomeMessage(User& user);

	// Listeners
	void onLeave(GroupLeaveEvent& event);
};

#endif /* FT_IRC_CORE */
