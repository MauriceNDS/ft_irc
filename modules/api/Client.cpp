#include "api/Client.hpp"
#include "api/Connection.hpp"

Client::Client(Connection *connection) : connection(connection) {
	connection->client = this;
}

Connection *Client::getConnection() const {
	return connection;
}

void Client::send(const string& message) const {
	connection->send(message.c_str(), message.length());
}

Client::~Client() {
	connection->client = NULL;
}
