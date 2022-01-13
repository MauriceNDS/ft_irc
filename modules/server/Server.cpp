#include "server/Server.hpp"

#include "core/Irc.hpp"

#include <fstream>
std::ifstream infile("simulation.txt");

void Server::simulate_join(Connection *connection, string name) {
	User *u = new User(connection);
	u->setNickName(name);
	Irc::getInstance().addUser(u);
}

void Server::listen() {
	Connection *base_connection = new Connection(0, sockaddr());
	Client *base = new User(base_connection);

	simulate_join(simulate_connect(1), "ArseneLeBG");
	simulate_join(simulate_connect(2), "SimonLePlusBG");
	simulate_join(simulate_connect(3), "Lucasquette");

	std::string line;

	while (std::getline(infile, line)) {
		if (!line.empty()) {
			std::cout << "< " << line << std::endl;
			MessageEvent event = MessageEvent(line, *base);
			Irc::getInstance().getCommandManager().post(event);
		}
	}

	delete base_connection;
	delete base;
}
