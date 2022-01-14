#include "server/Server.hpp"

#include "core/Irc.hpp"

#include <fstream>
std::ifstream infile("simulation.txt");

User *Server::simulate_join(Connection *connection, string name) {
	User *u = new User(connection);
	u->setNickName(name);
	Irc::getInstance().addUser(u);
	return u;
}

void Server::listen() {
	Connection *base_connection = new Connection(0, sockaddr());
	Client *base = new User(base_connection);

	simulate_join(simulate_connect(1), "ArseneLeBG");
	simulate_join(simulate_connect(2), "SimonLePlusBG");
	simulate_join(simulate_connect(3), "Lucasquette");

	std::string line;

	while (std::getline(std::cin, line)) {
	// while (std::getline(infile, line)) {
		if (!line.empty()) {
			MessageEvent event = MessageEvent(line, *base);
			Irc::getInstance().getCommandManager().post(event);
		}
	}

	for (map<int, Connection *>::iterator i = connections.begin(); i != connections.end(); ++i) {
		delete i->second;
	}
	delete base_connection;
	delete base;
}
