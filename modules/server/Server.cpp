#include "server/Server.hpp"

#include "core/Irc.hpp"

#include <fstream>
#include <algorithm>
#include <sstream>

#define MAX_BUFFER_LENGTH 512

Connection *Server::addConnection(const struct pollfd& connection, const struct sockaddr_in& addr) {
	Connection *newConnect = new Connection(connection, addr);
	connections.push_back(newConnect);
	return newConnect;
}

Server::Server(const string& name, const int port, const string& password) : name(name), host("127.0.0.1"), port(port), password(password) {
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

	addConnection(serverSocket, connectionConfig);

	connectionConfig.sin_family = AF_INET;
	connectionConfig.sin_addr.s_addr = INADDR_ANY;
	connectionConfig.sin_port = htons(this->port);

	// Can be protected
	bind(serverSocket.fd, (struct sockaddr *)&connectionConfig, sizeof(connectionConfig));

	// Can be protected
	listen(serverSocket.fd, 32);

}

const string& Server::getName() const {
	return name;
}

string Server::getSenderName() const {
	return connections[0]->getIP();
}

const string& Server::getHost() const {
	return host;
}

void Server::start() {
	vector<Connection *>::iterator it;

	for (map<const string, Plugin *>::const_iterator plugin = Irc::getInstance().getPluginLoader().getPlugins().begin(); plugin != Irc::getInstance().getPluginLoader().getPlugins().end(); plugin++)
		plugin->second->serverStarted();

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
	struct sockaddr_in newConnection;
	int clen;

	newSocket.events = POLLIN;
	while (true) {
		clen = sizeof(newConnection);
		if ((newSocket.fd = accept(Connection::sockets[0].fd, (struct sockaddr *)&newConnection, (socklen_t*)&clen)) < 0)
			break ;

		Irc::getInstance().addUser(new User(addConnection(newSocket, newConnection)));
	}
}

void Server::closeConnection(size_t index) {
	// Contains the server !
	Client *client = connections[index]->client;
	User *user = dynamic_cast<User *>(client);
	if (user)
		Irc::getInstance().removeUser(user);

	close(Connection::sockets[index].fd);
	connections.erase(connections.begin() + index);
	Connection::sockets.erase(Connection::sockets.begin() + index);
}

void Server::incomingRequest(size_t index) {
	char buffer[MAX_BUFFER_LENGTH];

	while (true) {
		int ret = recv(Connection::sockets[index].fd, buffer, MAX_BUFFER_LENGTH - 1, 0);
		if (ret < 0)
			return ;
		else if (ret == 0) {
			connections[index]->closeConnection = true;
			return ;
		}
		buffer[ret] = 0;
		connections[index]->request += buffer;
		if (connections[index]->request.find('\n') != string::npos) {
			string line = connections[index]->request;
			string request;

			line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
			std::istringstream ss(line.c_str());

			while (std::getline(ss, request, '\n')) {
				if (ss.eof() && !request.empty())
					connections[index]->request = request;
				else
					connections[index]->request.clear();
				std::cout << "    < '" << request << "`" << std::endl;
				MessageEvent event = MessageEvent(request, *connections[index]->client);
				Irc::getInstance().getCommandManager().process(event);
			}
		}
	}
}

Server::~Server() {
	for (size_t i = 0; i < connections.size(); i++) {
		close(Connection::sockets[i].fd);
		delete connections[i];
	}
	connections.clear();
}
