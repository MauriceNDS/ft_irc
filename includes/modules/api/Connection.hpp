#ifndef FT_IRC_SERVER_CONNECTION
#define FT_IRC_SERVER_CONNECTION

#include "ft_irc.hpp"

#include "api/Client.hpp"

#include <sys/socket.h>

class Client;

struct Connection {
	static vector<struct pollfd> sockets;

	const int fd;
	Client *client;
	string request;
	bool closeConnection;

	Connection(const struct pollfd& socket);

	void send(const char *str, int len);
};

#endif /* FT_IRC_SERVER_CONNECTION */
