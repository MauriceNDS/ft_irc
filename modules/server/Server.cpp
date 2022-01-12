#include "server/Server.hpp"

#include "core/Irc.hpp"

#include <fstream>
std::ifstream infile("example.txt");

void Server::listen() {
	User *u = new User("Simon");

	std::string line;

	while (std::getline(infile, line)) {
		if (!line.empty())
			Irc::getInstance().getCommandManager().post(line, nullptr);
	}

	delete u;
}
