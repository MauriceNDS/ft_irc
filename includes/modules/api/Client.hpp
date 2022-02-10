#ifndef FT_IRC_API_CLIENT
#define FT_IRC_API_CLIENT

#include "ft_irc.hpp"

#include "api/CommandSender.hpp"
#include "api/Connection.hpp"

struct Connection;

class Client : public CommandSender {
protected:
	Connection *const connection;

public:
	Client(Connection *connection);

	const Connection *getConnection() const {
		return connection;
	}

	void send(const string& message) const;

	virtual ~Client() = 0;
};

#endif /* FT_IRC_API_CLIENT */
