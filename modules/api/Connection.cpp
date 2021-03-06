#include "api/Connection.hpp"

vector<struct pollfd> Connection::sockets = vector<struct pollfd>();

Connection::Connection(const struct pollfd& socket, const struct sockaddr_in& addr) : fd(socket.fd), addr(addr), client(NULL), closeConnection(false) {
	sockets.push_back(socket);
}

void Connection::send(const char *str, int len) const {
	int ret = ::send(fd, str, len, 0);
	(void)ret;
}

string Connection::getIP() const {
	return ::itos(addr.sin_addr.s_addr & 0xFF) + '.'
		+ ::itos((addr.sin_addr.s_addr & 0xFF00) >> 8) + '.'
		+ ::itos((addr.sin_addr.s_addr & 0xFF0000) >> 16) + '.'
		+ ::itos((addr.sin_addr.s_addr & 0xFF000000) >> 24);
}