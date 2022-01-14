#ifndef FT_IRC_API_CLIENT
#define FT_IRC_API_CLIENT

#include "ft_irc.hpp"

#include "api/Connection.hpp"

#include "server/Response.hpp"

struct Connection;

class Client {
private:
	Connection *const connection;

public:
	Client(Connection *connection);

	const Connection *getConnection() {
		return connection;
	}

	void send(Response response) const {
		std::cout << "> " << response << std::endl;
	}

	virtual ~Client() = 0;
};

#endif /* FT_IRC_API_CLIENT */
