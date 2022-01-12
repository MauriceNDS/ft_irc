#ifndef FT_IRC_API_CLIENT
#define FT_IRC_API_CLIENT

#include "ft_irc.hpp"

#include "server/Connection.hpp"

struct Connection;

class Client {
private:
	Connection *connection;
    
public:
	Client(Connection *connection);

	const Connection *getConnection() {
		return connection;
	}

	virtual ~Client() = 0;
};

#endif /* FT_IRC_API_CLIENT */
