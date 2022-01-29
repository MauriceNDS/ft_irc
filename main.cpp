#include "ft_irc.hpp"

// #include "core/Irc.hpp"

// #include <cstdlib>

// bool isNumber(const std::string& s) {
//     std::string::const_iterator it = s.begin();
//     while (it != s.end() && std::isdigit(*it))
// 		++it;
//     return !s.empty() && it == s.end();
// }

// int main(int argc, char *argv[]) {
// 	if (argc != 3 || !isNumber(argv[1])) {
// 		std::cout << "Invalid arguments" << std::endl;
// 		exit(1);
// 	}
// 	Irc irc("International Robbers Classification", std::atoi(argv[1]), argv[2]);
// 	irc.start();
// 	return 0;
// }

#include <dlfcn.h>
#include "api/Plugin.hpp"

void loadPlugin(char *name) {
	void *dl_handle = dlopen(name, RTLD_LAZY | RTLD_LOCAL);
	if (!dl_handle) {
		std::cerr << "Cannot open " << name << std::endl;
		return;
	}
	Plugin *(*getPlugin)() = reinterpret_cast<Plugin *(*)()>(dlsym(dl_handle, "getPlugin"));
	if (!getPlugin) {
		std::cerr << "Cannot load " << name << ": symbol `getPlugin' not found." << std::endl;
		return;
	}
	Plugin *plugin = getPlugin();

	plugin->onStart();
	plugin->onStop();
}

int main() {
	loadPlugin((char *)"plugins/test.so");
	return 0;
}

