#include "ft_irc.hpp"

#include "core/Irc.hpp"

#include "signal.h"

void handle_sigint(int) {
	Irc::getInstance().getServer().stop();
}

int main(int argc, char *argv[]) {
	if (argc != 3 || (string(argv[1]).find_first_not_of("0123456789") != string::npos)) {
		std::cout << "Invalid arguments" << std::endl;
		exit(1);
	}

	vector<string> files;

	Irc irc("ft_irc", std::atoi(argv[1]), argv[2], files);

	signal(SIGINT, &handle_sigint);

	irc.start();
	std::cout << "Goodbye!" << std::endl;
	return EXIT_SUCCESS;
}
