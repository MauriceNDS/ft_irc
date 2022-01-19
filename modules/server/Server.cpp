#include "server/Server.hpp"

#include "core/Irc.hpp"

#include <fstream>

#define MAX_BUFFER_LENGTH 4096


Server::Server(const string& name) : name(name) {
	Connection *serverConnection;
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

	connectionConfig.sin_family = AF_INET;
	connectionConfig.sin_addr.s_addr = INADDR_ANY;
	connectionConfig.sin_port = htons(8080);

	// Can be protected
	bind(serverSocket.fd, (struct sockaddr *)&connectionConfig, sizeof(connectionConfig));

	// Can be protected
	listen(serverSocket.fd, 32);

	serverConnection = new Connection(serverSocket);
	connections.push_back(serverConnection);
}

const string& Server::getName() {
	return name;
}

void Server::start() {
	vector<Connection *>::iterator it;

	std::cout << "Waiting for connections..." << std::endl;
	while (true) {
		poll(&connections[0]->socket, connections.size(), -1);
		for (it = connections.begin(); it != connections.end(); it++) {
			if ((*it)->socket.revents == 0)
				continue ;
			else
				std::cout << (*it)->socket.revents << std::endl;
			if ((*it)->socket.fd == connections[0]->socket.fd) {
				std::cout << "  IncomingConnection..." << std::endl;
				incomingConnection();
				break ;
			}
			else {
				std::cout << "  IncomingRequest..." << std::endl;
				incomingRequest(it);
				if ((*it)->closeConnection) {
					std::cout << "  CloseConnection..." << std::endl;
					closeConnection(it);
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
		if ((newSocket.fd = accept(connections[0]->socket.fd, NULL, NULL)) < 0) {
			if (errno != EWOULDBLOCK)
				exit(1);
			break ;
		}
		Connection *incomingConnection = new Connection(newSocket);

		connections.push_back(incomingConnection);
	}
}

void Server::closeConnection(vector<Connection *>::iterator connection) {
	close((*connection)->socket.fd);
	connections.erase(connection);
}

void Server::incomingRequest(vector<Connection *>::iterator connection) {
	vector<char> buffer(MAX_BUFFER_LENGTH);
	string request;

	while (true) {
		int ret = recv((*connection)->socket.fd, &buffer[0], buffer.size(), 0);
		if (ret < 0) {
			if (errno != EWOULDBLOCK) {
				(*connection)->closeConnection = true;
			}
			return ;
		}
		else if (ret == 0) {
			(*connection)->closeConnection = true;
			return ;
		}
		std::cout << "    Message recieved: " << &buffer[0] << "..." << std::endl;
		request.append(buffer.cbegin(), buffer.cend());
		buffer.clear();
		buffer.resize(MAX_BUFFER_LENGTH);
		if (request.find('\n') != string::npos) {
			ret = send((*connection)->socket.fd, request.c_str(), request.length(), 0);
			request.clear();
			if (ret < 0) {
				(*connection)->closeConnection = true;
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