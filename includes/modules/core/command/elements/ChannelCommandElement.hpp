#ifndef FT_IRC_CORE_CHANNEL_COMMAND_ELEMENT
#define FT_IRC_CORE_CHANNEL_COMMAND_ELEMENT

#include "ft_irc.hpp"

#include "api/Channel.hpp"
#include "api/command/CommandElement.hpp"
#include "api/event/MessageEvent.hpp"

class ChannelCommandElement : public CommandElement {
private:
	bool createIfUnknown;
public:
	ChannelCommandElement(bool createIfUnknown) : createIfUnknown(createIfUnknown) {};
	
	void *parseValue(const string& arg, MessageEvent& event) const {
		if (Channel::isValidIdentifier(arg)) {
			Channel *channel;
			if (channel = Irc::getInstance().findChannel(arg)) {
				return (channel);
			} else if (createIfUnknown) {
				channel = new Channel(arg);
				Irc::getInstance().addChannel(channel);
				return (channel);
			}
		}
		event.getSender().send(ERR_NOSUCHCHANNEL);
		return NULL;
	}
};

#endif /* FT_IRC_CORE_CHANNEL_COMMAND_ELEMENT */
