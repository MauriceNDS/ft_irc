#ifndef FT_IRC_SERVER_CONNECTION
#define FT_IRC_SERVER_CONNECTION

#include "ft_irc.hpp"

#include "api/Client.hpp"

#include <sys/socket.h>

struct Connection {
	Client *client;
	int socket;
	sockaddr address;

	Connection(int socket, sockaddr address) : client(nullptr), socket(socket), address(address) {}
};

#endif /* FT_IRC_SERVER_CONNECTION */
