#ifndef FT_IRC_API_SERVER
#define FT_IRC_API_SERVER

#include "ft_irc.hpp"

#include "core/Irc.hpp"

#include "api/User.hpp"

#include <fstream>
std::ifstream infile("example.txt");

class Server {
private:
	string name;
    
public:
	// TODO test
	Server(const string& name) : name(name) {}

	const string& getName() {
		return name;
	}

	void Server::listen() {
		User *u = new User("Simon");

		std::string line;

		while (std::getline(infile, line)) {
			if (!line.empty())
				Irc::getInstance().getCommandManager().post(line, nullptr);
		}

		delete u;
	}
};

#endif /* FT_IRC_API_SERVER */
