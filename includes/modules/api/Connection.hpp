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

	string getIP() const;
};

#endif /* FT_IRC_SERVER_CONNECTION */
