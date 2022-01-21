#ifndef FT_IRC_SERVER_SERVER
#define FT_IRC_SERVER_SERVER

#include "ft_irc.hpp"

#include "api/User.hpp"
#include "api/Connection.hpp"
#include <unistd.h>

class Server {
private:
	string name;
	vector<Connection *> connections;
	vector<struct pollfd> allSockets;
	struct sockaddr_in connectionConfig;

	void incomingConnection();
	void incomingRequest(size_t index);
	void closeConnection(size_t	index);
	void addConnection(const struct pollfd &connection);

public:
	Server(const string& name);

	const string& getName();

	void start();

	~Server();
};

#endif /* FT_IRC_SERVER_SERVER */
