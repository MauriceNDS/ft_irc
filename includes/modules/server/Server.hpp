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
	struct sockaddr_in connectionConfig;

	void incomingConnection();
	void incomingRequest(vector<Connection *>::iterator connection);
	void closeConnection(vector<Connection *>::iterator connection);

public:
	Server(const string& name);

	const string& getName();

	void start();

	~Server();
};

#endif /* FT_IRC_SERVER_SERVER */
