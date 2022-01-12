#include "api/Client.hpp"

Client::Client(Connection *connection) : connection(connection) {
	connection->client = this;
}

Client::~Client() {}
