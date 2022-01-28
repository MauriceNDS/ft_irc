#include "api/Connection.hpp"

#include "core/Irc.hpp"

vector<struct pollfd> Connection::sockets = vector<struct pollfd>();

Connection::Connection(const struct pollfd& socket) : fd(socket.fd), client(NULL), closeConnection(false) {
	sockets.push_back(socket);
}

void Connection::send(const char *str, int len) {
	int ret = ::send(fd, str, len, 0);
	(void)ret;
}