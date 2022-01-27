#include "server/Server.hpp"

#include "core/Irc.hpp"

#include <fstream>

#define MAX_BUFFER_LENGTH 4096

Connection *Server::addConnection(const struct pollfd &connection) {
	Connection *newConnect = new Connection(connection);
	connections.push_back(newConnect);
	return newConnect;
}

Server::Server(const string& name) : name(name) {
	struct pollfd serverSocket;
	int opt = 1;

	std::cout << "Setting up the server..." << std::endl;

	// Can be protected
	serverSocket.fd = socket(AF_INET, SOCK_STREAM, 0);
	serverSocket.events = POLLIN;

	// Can be protected -- Allow socket descriptor to be reusable
	setsockopt(serverSocket.fd, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt));
	opt = 1;

	// Can be protected -- Set socket to be nonblocking
	ioctl(serverSocket.fd, FIONBIO, (char *)&opt);

	addConnection(serverSocket);


	connectionConfig.sin_family = AF_INET;
	connectionConfig.sin_addr.s_addr = INADDR_ANY;
	connectionConfig.sin_port = htons(8080);

	// Can be protected
	bind(serverSocket.fd, (struct sockaddr *)&connectionConfig, sizeof(connectionConfig));

	// Can be protected
	listen(serverSocket.fd, 32);

}

const string& Server::getName() const {
	return name;
}

void Server::start() {
	vector<Connection *>::iterator it;

	std::cout << "Waiting for connections..." << std::endl;
	while (true) {
		poll(&Connection::sockets[0], Connection::sockets.size(), -1);
		for (size_t i = 0; i < Connection::sockets.size(); i++) {
			if (Connection::sockets[i].revents == 0)
				continue ;
			if (Connection::sockets[i].fd == Connection::sockets[0].fd) {
				std::cout << "  IncomingConnection..." << std::endl;
				incomingConnection();
				break ;
			}
			else {
				std::cout << "  IncomingRequest..." << std::endl;
				incomingRequest(i);
				if (connections[i]->closeConnection) {
					std::cout << "  CloseConnection..." << std::endl;
					closeConnection(i);
					break ;
				}
			}
		}
	}
}

void Server::incomingConnection() {
	struct pollfd newSocket;

	newSocket.events = POLLIN;

	while (true) {
		if ((newSocket.fd = accept(Connection::sockets[0].fd, NULL, NULL)) < 0) {
			if (errno != EWOULDBLOCK)
				exit(1);
			break ;
		}
		Irc::getInstance().addUser(new User(addConnection(newSocket)));
	}
}

void Server::closeConnection(size_t index) {
	close(Connection::sockets[index].fd);
	connections.erase(connections.begin() + index);
	Connection::sockets.erase(Connection::sockets.begin() + index);
}

void Server::incomingRequest(size_t index) {
	char buffer[MAX_BUFFER_LENGTH];

	while (true) {
		int ret = recv(Connection::sockets[index].fd, buffer, MAX_BUFFER_LENGTH - 1, 0);
		if (ret < 0) {
			if (errno != EWOULDBLOCK) {
				connections[index]->closeConnection = true;
			}
			return ;
		}
		else if (ret == 0) {
			connections[index]->closeConnection = true;
			return ;
		}
		buffer[ret] = 0;
		connections[index]->request += buffer;
		if (connections[index]->request.find('\n') != string::npos) {
			string line = connections[index]->request;

			line = line.substr(0, line.size() - 1);
			std::cout << "    < '" << line << "`" << std::endl;

			MessageEvent event = MessageEvent(line, *connections[1]->client);
			Irc::getInstance().getCommandManager().process(event);

			connections[index]->request.clear();
		}
	}
}

Server::~Server() {
	for (size_t i = 0; i < connections.size(); i++) {
		close(Connection::sockets[i].fd);
		free(connections[i]);
	}
}