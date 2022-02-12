#ifndef FT_IRC_SERVER_CONNECTION
#define FT_IRC_SERVER_CONNECTION

#include "ft_irc.hpp"

#include "api/Client.hpp"

#include <sys/socket.h>
#include <netinet/in.h>

#include <sstream>

class Client;

class Connection {
private:
	string itoa(int value) const {
		std::ostringstream out;
		out << value;
		return out.str();
	}

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
		return itoa(addr.sin_addr.s_addr & 0xFF) + '.'
			+ itoa((addr.sin_addr.s_addr & 0xFF00) >> 8) + '.'
			+ itoa((addr.sin_addr.s_addr & 0xFF0000) >> 16) + '.'
			+ itoa((addr.sin_addr.s_addr & 0xFF000000) >> 24);
	}
};

#endif /* FT_IRC_SERVER_CONNECTION */
