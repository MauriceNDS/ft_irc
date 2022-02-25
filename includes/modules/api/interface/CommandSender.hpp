#ifndef FT_IRC_API_COMMAND_SENDER
#define FT_IRC_API_COMMAND_SENDER

#include "ft_irc.hpp"
#include "api/interface/Nameable.hpp"

class CommandSender : public Nameable {
public:
	virtual void send(const string& message) const = 0;

	virtual string getSenderName() const = 0;

	virtual ~CommandSender() {}
};

#endif /* FT_IRC_API_COMMAND_SENDER */
