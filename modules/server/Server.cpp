#include "server/Server.hpp"

#include "core/Irc.hpp"

#include "api/User.hpp"

#include <fstream>
#include <algorithm>
#include <sstream>
#include <cstring>

#define MAX_BUFFER_LENGTH 512

Connection *Server::addConnection(const struct pollfd& connection, const struct sockaddr_in& addr) {
	Connection *newConnect = new Connection(connection, addr);
	connections.push_back(newConnect);
	return newConnect;
}

Server::Server(const string& name, const int port, const string& password) : name(name), host("127.0.0.1"), port(port), password(password), running(true) {}

void Server::send(const string& message) const {
	std::cout << message << std::endl;
}

string Server::getName() const {
	return name;
}

string Server::getSenderName() const {
	return getConnection().getIP();
}

const string& Server::getHost() const {
	return host;
}

const Connection& Server::getConnection() const {
	return *(connections[0]);
}

const string& Server::getPassword() const {
	return password;
}

void Server::start() {
	struct pollfd serverSocket;
	int opt = 1;

	std::cout << "[INFO] Setting up the server..." << std::endl;
	
	if ((serverSocket.fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		std::cerr << std::strerror(errno) << std::endl;
		return;
	}
	serverSocket.events = POLLIN;

	if (setsockopt(serverSocket.fd, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) == -1) {
		std::cerr << std::strerror(errno) << std::endl;
		return;
	}
	opt = 1;

	if (ioctl(serverSocket.fd, FIONBIO, (char *)&opt) == -1) {
		std::cerr << std::strerror(errno) << std::endl;
		return;
	}

	connectionConfig.sin_family = AF_INET;
	connectionConfig.sin_addr.s_addr = INADDR_ANY;
	connectionConfig.sin_port = htons(this->port);

	if (bind(serverSocket.fd, (struct sockaddr *)&connectionConfig, sizeof(connectionConfig))) {
		std::cerr << std::strerror(errno) << std::endl;
		return;
	}

	addConnection(serverSocket, connectionConfig);

	if (listen(serverSocket.fd, 32) == -1) { 
		std::cerr << std::strerror(errno) << std::endl;
		return;
	}

	vector<Connection *>::iterator it;

	for (map<const string, Plugin *>::const_iterator plugin = Irc::getInstance().getPluginLoader().getPlugins().begin(); plugin != Irc::getInstance().getPluginLoader().getPlugins().end(); plugin++)
		plugin->second->serverStarted();

	std::cout << "[INFO] Waiting for connections..." << std::endl;
	while (running) {
		poll(&Connection::sockets[0], Connection::sockets.size(), -1);
		for (size_t i = 0; i < Connection::sockets.size(); i++) {
			if (Connection::sockets[i].revents == 0)
				continue;
			if (Connection::sockets[i].fd == Connection::sockets[0].fd) {
				std::cout << "[INFO] New connection" << std::endl;
				incomingConnection();
				break;
			}
			else {
				incomingRequest(i);
				if (connections[i]->closeConnection) {
					closeConnection(i);
					removeConnection(i);
					break;
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
	clen = sizeof(newConnection);
	while (running) {
		if ((newSocket.fd = accept(Connection::sockets[0].fd, (struct sockaddr *)&newConnection, (socklen_t*)&clen)) < 0)
			break;

		Irc::getInstance().addUser(new User(addConnection(newSocket, newConnection)));
	}
}

void Server::closeConnection(size_t index) {
	Client *client = connections[index]->client;
	User *user = dynamic_cast<User *>(client);
	if (user)
		Irc::getInstance().removeUser(*user);

	shutdown(Connection::sockets[index].fd, SHUT_RDWR);
	close(Connection::sockets[index].fd);
	Connection::sockets.erase(Connection::sockets.begin() + index);
}

void Server::removeConnection(size_t index) {
	delete connections[index];
	connections.erase(connections.begin() + index);
}

void Server::incomingRequest(size_t index) {
	char buffer[MAX_BUFFER_LENGTH];

	while (running) {
		int ret = recv(Connection::sockets[index].fd, buffer, MAX_BUFFER_LENGTH - 1, 0);
		if (ret < 0)
			return;
		else if (ret == 0) {
			connections[index]->closeConnection = true;
			return;
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
				MessageEvent event = MessageEvent(request, *connections[index]->client);
				Irc::getInstance().getCommandManager().process(event);
				if (!running)
					return ;
			}
		}
	}
}

void Server::stop() { running = false; }

Server::~Server() {
	for (map<const string, Plugin *>::const_iterator plugin = Irc::getInstance().getPluginLoader().getPlugins().begin(); plugin != Irc::getInstance().getPluginLoader().getPlugins().end(); plugin++)
		plugin->second->serverStopping();

	size_t i = connections.size();
	while (i) {
		i--;
		closeConnection(i);
		delete connections[i];
	}
	connections.clear();

	for (map<const string, Plugin *>::const_iterator plugin = Irc::getInstance().getPluginLoader().getPlugins().begin(); plugin != Irc::getInstance().getPluginLoader().getPlugins().end(); plugin++)
		plugin->second->serverStopped();
}
