#ifndef FT_IRC_API_COMMAND_SENDER
#define FT_IRC_API_COMMAND_SENDER

#include "ft_irc.hpp"

#include "server/Response.hpp"

struct Connection;

class CommandSender {
public:
	virtual void send(Response message) const = 0;

	virtual ~CommandSender() {}
};

#endif /* FT_IRC_API_COMMAND_SENDER */
