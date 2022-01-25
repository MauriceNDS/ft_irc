#ifndef FT_IRC_API_CLIENT
#define FT_IRC_API_CLIENT

#include "ft_irc.hpp"

#include "api/CommandSender.hpp"
#include "api/Connection.hpp"

struct Connection;

class Client : public CommandSender {
private:
	Connection *const connection;

public:
	Client(Connection *connection);

	const Connection *getConnection() {
		return connection;
	}

	void send(const string& message) const {
		std::cout << "> " << message << std::endl;
	}

	virtual ~Client() = 0;
};

#endif /* FT_IRC_API_CLIENT */
