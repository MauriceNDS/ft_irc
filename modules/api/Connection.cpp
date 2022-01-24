#include "api/Connection.hpp"

#include "core/Irc.hpp"

vector<struct pollfd> Connection::sockets = vector<struct pollfd>();

Connection::Connection(const struct pollfd& socket) : client(NULL), closeConnection(false) {
	sockets.push_back(socket);
}