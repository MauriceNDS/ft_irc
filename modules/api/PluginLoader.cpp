#include "api/PluginLoader.hpp"

Plugin *PluginLoader::loadPlugin(const string& name) {
	void *dl_handle = dlopen(name.c_str(), RTLD_LAZY | RTLD_LOCAL);
	if (!dl_handle) {
		std::cerr << "Plugin loader: Cannot open " << name << std::endl;
		return NULL;
	}
	Plugin *(*getPlugin)() = reinterpret_cast<Plugin *(*)()>(reinterpret_cast<long>(dlsym(dl_handle, "getPlugin")));
	if (!getPlugin) {
		std::cerr << "Plugin loader: Cannot load " << name << ": symbol `getPlugin' not found." << std::endl;
		return NULL;
	}
	return getPlugin();
}

void PluginLoader::loadPlugins(const vector<string>& files) {
	for (vector<string>::const_iterator file = files.begin(); file != files.end(); file++) {
		Plugin *plugin = loadPlugin(*file);
		if (plugin) {
			string id = plugin->getId();

			if (id.length() < 4 || id.find_first_not_of("abcdefghijklmnopqrstuvwxyz._") != string::npos) {
				std::cerr << "Plugin loader : Unable to load " << id << ": invalid id." << std::endl;
				delete plugin;
				continue;
			}
			if (plugins.count(id)) {
				std::cerr << "Plugin loader : Unable to load " << id << ": a plugin already exists with the same id." << std::endl;
				delete plugin;
				continue;
			}
			plugins[id] = plugin;
			std::cout << "Plugin loader: " << id << " (aka " << *file << ") loaded" << std::endl;
		}
	}
}

const Plugin *PluginLoader::getPlugin(const string& id) const {
	map<const string, Plugin *>::const_iterator plugin = plugins.find(id);
	if (plugin == plugins.end())
		return NULL;
	return plugin->second;
}

const map<const string, Plugin *>& PluginLoader::getPlugins() const {
	return plugins;
}

PluginLoader::~PluginLoader() {
	for (map<const string, Plugin *>::const_iterator plugin = plugins.begin(); plugin != plugins.end(); plugin++)
		delete plugin->second;
}