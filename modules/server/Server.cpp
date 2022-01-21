#include "server/Server.hpp"

#include "core/Irc.hpp"

#include <fstream>

#define MAX_BUFFER_LENGTH 4096

void Server::addConnection(const struct pollfd &connection) {
	Connection *newConnect = new Connection(connection);
	connections.push_back(newConnect);
	allSockets.push_back(connection);
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

const string& Server::getName() {
	return name;
}

void Server::start() {
	vector<Connection *>::iterator it;

	std::cout << "Waiting for connections..." << std::endl;
	while (true) {
		poll(&allSockets[0], allSockets.size(), -1);
		for (size_t i = 0; i < allSockets.size(); i++) {
			if (allSockets[i].revents == 0)
				continue ;
			if (allSockets[i].fd == allSockets[0].fd) {
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
		if ((newSocket.fd = accept(allSockets[0].fd, NULL, NULL)) < 0) {
			if (errno != EWOULDBLOCK)
				exit(1);
			break ;
		}
		addConnection(newSocket);
	}
}

void Server::closeConnection(size_t index) {
	close(allSockets[index].fd);
	connections.erase(connections.begin() + index);
	allSockets.erase(allSockets.begin() + index);
}

void Server::incomingRequest(size_t index) {
	vector<char> buffer(MAX_BUFFER_LENGTH);

	while (true) {
		int ret = recv(allSockets[index].fd, &buffer[0], buffer.size(), 0);
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
		connections[index]->request.append(buffer.cbegin(), buffer.cend());
		buffer.clear();
		buffer.resize(MAX_BUFFER_LENGTH);
		if (connections[index]->request.find('\n') != string::npos) {
			std::cout << "    Message recieved: " << connections[index]->request;
			ret = send(allSockets[index].fd, connections[index]->request.c_str(), connections[index]->request.length(), 0);
			connections[index]->request.clear();
			if (ret < 0) {
				connections[index]->closeConnection = true;
				return ;
			}
		}
	}
}

Server::~Server() {
	vector<Connection *>::iterator it;
	for (it = connections.begin(); it != connections.end(); it++) {
		close((*it)->socket.fd);
		free(*it);
	}
}