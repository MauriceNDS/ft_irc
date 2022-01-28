#include "server/Server.hpp"

#include "core/Irc.hpp"

#include <fstream>

Connection *Server::simulate_connect(int socket) {
	Connection *connection = new Connection(socket, sockaddr());
	connections[socket] = connection;
	return connection;
}

User *Server::simulate_join(Connection *connection, string name) {
	User *u = new User(connection);
	u->setNickName(name);
	Irc::getInstance().addUser(u);
	return u;
}

void Server::listen() {
	simulate_join(simulate_connect(1), "ArseneLeBG");
	simulate_join(simulate_connect(2), "SimonLePlusBG");
	simulate_join(simulate_connect(3), "Lucasquette");

	std::string line;

	while (std::getline(std::cin, line)) {
		if (!line.empty()) {
			MessageEvent event = MessageEvent(line, *connections[1]->client);
			Irc::getInstance().getCommandManager().process(event);
		}
	}

	for (map<int, Connection *>::iterator i = connections.begin(); i != connections.end(); ++i) {
		delete i->second;
	}
}
