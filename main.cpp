#include "ft_irc.hpp"

#include "core/Irc.hpp"

#include <cstdlib>

bool isNumber(const std::string& s) {
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it))
		++it;
    return !s.empty() && it == s.end();
}

int main(int argc, char *argv[]) {
	if (argc != 3 || !isNumber(argv[1])) {
		std::cout << "Invalid arguments" << std::endl;
		exit(1);
	}
	Irc irc("10.1.8.2", std::atoi(argv[1]), argv[2]);
	irc.start();
	return 0;
}
