#ifndef FT_IRC_CORE_CHANNEL_COMMAND_ELEMENT
#define FT_IRC_CORE_CHANNEL_COMMAND_ELEMENT

#include "ft_irc.hpp"
#include "core/Irc.hpp"

#include "api/Channel.hpp"
#include "api/command/CommandElement.hpp"
#include "api/event/MessageEvent.hpp"

class ChannelCommandElement : public CommandElement {
private:
	bool createIfUnknown;

public:
	ChannelCommandElement(bool createIfUnknown);

	void *parseValue(string arg, MessageEvent& event) const;
};

#endif /* FT_IRC_CORE_CHANNEL_COMMAND_ELEMENT */
