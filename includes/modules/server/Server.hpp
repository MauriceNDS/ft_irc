#ifndef FT_IRC_SERVER_SERVER
#define FT_IRC_SERVER_SERVER

#include "ft_irc.hpp"

#include "api/User.hpp"
#include "api/Connection.hpp"

#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <poll.h>

class Server : public CommandSender {
private:
	string name;
	string host;
	vector<Connection *> connections;
	struct sockaddr_in connectionConfig;
	const int port;
	const string password;

	void incomingConnection();
	void incomingRequest(size_t index);
	void closeConnection(size_t	index);
	Connection *addConnection(const struct pollfd &connection, const struct sockaddr_in& addr);

public:
	Server(const string& name, const int port, const string& password);

	void send(const string& message) const {
		std::cout << message << std::endl;
	}

	const string& getName() const;
	const string& getHost() const;

	void start();

	~Server();
};

#endif /* FT_IRC_SERVER_SERVER */
