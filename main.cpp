#include "ft_irc.hpp"

#include "core/Irc.hpp"
#include "api/Plugin.hpp"

#include <cstdlib>
#include <dlfcn.h>

Plugin *loadPlugin(const string& name) {
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

int main(int argc, char *argv[]) {
	if (argc != 3 || (string(argv[1]).find_first_not_of("0123456789") != string::npos)) {
		std::cout << "Invalid arguments" << std::endl;
		exit(1);
	}

	vector<string> files;
	files.push_back("test.so");

	vector<Plugin *> plugins;
	for (vector<string>::iterator file = files.begin(); file != files.end(); file++) {
		Plugin *plugin = loadPlugin(*file);
		if (plugin) {
			plugins.push_back(plugin);
			std::cout << "Plugin loader: " << *file << " loaded" << std::endl;
		}
	}

	Irc irc("127.0.0.1", std::atoi(argv[1]), argv[2], plugins);

	irc.start();
	return 0;
}
