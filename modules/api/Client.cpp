#include "api/Client.hpp"

Client::Client(Connection *connection) : connection(connection) {
	connection->client = this;
}

void Client::send(const string& message) const {
	string info = message.substr(0, message.size() - 1);
	std::cout << "    > `" << info << "'" << std::endl;
	connection->send(message.c_str(), message.length());
}

Client::~Client() {}
