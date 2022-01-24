#ifndef FT_IRC_SERVER_CONNECTION
#define FT_IRC_SERVER_CONNECTION

#include "ft_irc.hpp"

#include "api/Client.hpp"

#include <sys/socket.h>

class Client;

struct Connection {
	Client *client;
	static vector<struct pollfd> sockets;
	string request;
	bool closeConnection;

	Connection(const struct pollfd& socket);
};

#endif /* FT_IRC_SERVER_CONNECTION */
