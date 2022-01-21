#ifndef FT_IRC_SERVER_CONNECTION
#define FT_IRC_SERVER_CONNECTION

#include "ft_irc.hpp"

#include "api/Client.hpp"

#include <sys/socket.h>

class Client;

struct Connection {
	Client *client;
	struct pollfd socket;
	string request;
	bool closeConnection;

	Connection(const struct pollfd& socket) : client(NULL), socket(socket), closeConnection(false) {}
};

#endif /* FT_IRC_SERVER_CONNECTION */
