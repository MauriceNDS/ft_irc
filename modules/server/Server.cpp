#include "server/Server.hpp"

#include "core/Irc.hpp"

#include <fstream>
std::ifstream infile("example.txt");

void Server::simulate_join(Connection *connection, string name) {
	User *u = new User(connection);
	u->setNickName(name);
	Irc::getInstance().addUser(u);
}

void Server::listen() {
	simulate_join(simulate_connect(1), "ArseneLeBG");
	simulate_join(simulate_connect(2), "SimonLePlusBG");
	simulate_join(simulate_connect(3), "Lucasquette");

	std::string line;

	while (std::getline(infile, line)) {
		if (!line.empty())
			Irc::getInstance().getCommandManager().post(line, nullptr);
	}
}
