#ifndef FT_IRC_API_PLUGIN_LOADER
#define FT_IRC_API_PLUGIN_LOADER

#include "ft_irc.hpp"

#include "api/interface/CommandSender.hpp"
#include "api/Connection.hpp"
#include "api/Plugin.hpp"

#include <cstdlib>
#include <dlfcn.h>

class Connection;

class PluginLoader {
private:
	map<const string, Plugin *> plugins;

	Plugin *loadPlugin(const string& name);

public:
	void loadPlugins(const vector<string>& files);

	const Plugin *getPlugin(const string& id) const;

	const map<const string, Plugin *>& getPlugins() const;

	~PluginLoader();
};

#endif /* FT_IRC_API_PLUGIN_LOADER */
