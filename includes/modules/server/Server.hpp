#ifndef FT_IRC_SERVER_SERVER
#define FT_IRC_SERVER_SERVER

#include "ft_irc.hpp"

#include "server/Connection.hpp"

class Server {
private:
	string name;
	map<int, Connection *> connections;

public:
	Server(const string& name) : name(name) {}

	const string& getName() {
		return name;
	}

	void listen();
};

#endif /* FT_IRC_SERVER_SERVER */
