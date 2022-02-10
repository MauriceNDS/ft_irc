#include "ft_irc.hpp"

#include "core/Irc.hpp"

int main(int argc, char *argv[]) {
	if (argc != 3 || (string(argv[1]).find_first_not_of("0123456789") != string::npos)) {
		std::cout << "Invalid arguments" << std::endl;
		exit(1);
	}

	vector<string> files;
	files.push_back("test.so");
	files.push_back("test2.so");

	Irc irc("ft_irc", std::atoi(argv[1]), argv[2], files);
	irc.start();
	return 0;
}
