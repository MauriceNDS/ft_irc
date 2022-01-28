#include "api/Client.hpp"

Client::Client(Connection *connection) : connection(connection) {
	connection->client = this;
}

void Client::send(const string& message) const {
	connection->send(message.c_str(), message.length());
}

Client::~Client() {}
