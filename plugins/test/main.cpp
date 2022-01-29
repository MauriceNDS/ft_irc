#include "ft_irc.hpp"
#include "api/Plugin.hpp"

class TestPlugin : public Plugin {
public:
	void onStart() {
		std::cout << "Started" << std::endl;
	}

	void onStop() {
		std::cout << "Stopped" << std::endl;
	}
};

extern "C" Plugin *getPlugin() {
	std::cout << "Called" << std::endl;
	return new TestPlugin();
}
