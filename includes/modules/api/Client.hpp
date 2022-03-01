#ifndef FT_IRC_API_CLIENT
#define FT_IRC_API_CLIENT

#include "ft_irc.hpp"

#include "api/interface/CommandSender.hpp"

class Connection;

class Client : public CommandSender {
protected:
	Connection *const connection;

public:
	Client(Connection *connection);

	Connection *getConnection() const;

	virtual void send(const string& message) const;

	virtual ~Client() = 0;
};

#endif /* FT_IRC_API_CLIENT */
