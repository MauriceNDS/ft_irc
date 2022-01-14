#ifndef FT_IRC_SERVER_SERVER
#define FT_IRC_SERVER_SERVER

#include "ft_irc.hpp"

#include "api/User.hpp"

#include "server/Connection.hpp"

class Server {
private:
	string name;
	map<int, Connection *> connections;

	Connection *simulate_connect(int socket) {
		Connection *connection = new Connection(socket, sockaddr());
		connections[socket] = connection;
		return connection;
	}

	User *simulate_join(Connection *connection, string name);

public:
	Server(const string& name) : name(name) {}

	const string& getName() {
		return name;
	}

	void listen();
};

#endif /* FT_IRC_SERVER_SERVER */
