#ifndef FT_IRC_CORE_CHANNEL_COMMAND_ELEMENT
#define FT_IRC_CORE_CHANNEL_COMMAND_ELEMENT

#include "ft_irc.hpp"

#include "api/Channel.hpp"
#include "api/command/CommandElement.hpp"
#include "api/event/MessageEvent.hpp"

class ChannelCommandElement : public CommandElement {
public:
	void *parseValue(const string& arg, MessageEvent& event) const {
		if (Channel::isValidIdentifier(arg)) {
		}
		// event.getSender().send(ERR_NOSUCHCHANNEL);
		return NULL;
	}
};

#endif /* FT_IRC_CORE_CHANNEL_COMMAND_ELEMENT */
