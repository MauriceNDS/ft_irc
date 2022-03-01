#ifndef FT_IRC_SERVER_CONNECTION
#define FT_IRC_SERVER_CONNECTION

#include "ft_irc.hpp"

#include <sys/socket.h>
#include <netinet/in.h>
#include <poll.h>

class Client;

class Connection {
public:
	static vector<struct pollfd> sockets;

	const int fd;
	const struct sockaddr_in addr;
	Client *client;
	string request;
	bool closeConnection;

	Connection(const struct pollfd& socket, const struct sockaddr_in& addr);

	void send(const char *str, int len) const;

	string getIP() const {
		return ::itos(addr.sin_addr.s_addr & 0xFF) + '.'
			+ ::itos((addr.sin_addr.s_addr & 0xFF00) >> 8) + '.'
			+ ::itos((addr.sin_addr.s_addr & 0xFF0000) >> 16) + '.'
			+ ::itos((addr.sin_addr.s_addr & 0xFF000000) >> 24);
	}
};

#endif /* FT_IRC_SERVER_CONNECTION */
