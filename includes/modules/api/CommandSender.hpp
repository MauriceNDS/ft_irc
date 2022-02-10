#ifndef FT_IRC_API_COMMAND_SENDER
#define FT_IRC_API_COMMAND_SENDER

#include "ft_irc.hpp"

class Connection;

class CommandSender {
public:
	virtual void send(const string& message) const = 0;

	virtual const string& getName() const = 0;

	virtual ~CommandSender() {}
};

#endif /* FT_IRC_API_COMMAND_SENDER */
