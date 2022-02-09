#ifndef FT_IRC_CORE_MSGTARGET_COMMAND_ELEMENT
#define FT_IRC_CORE_MSGTARGET_COMMAND_ELEMENT

#include "ft_irc.hpp"

#include "core/Irc.hpp"

#include "api/User.hpp"
#include "api/Channel.hpp"
#include "api/command/CommandElement.hpp"
#include "api/event/MessageEvent.hpp"

class MsgToCommandElement : public CommandElement {
public:
	const ResponseSpec& notProvidedResponse() const {
		return ResponseTypes::ERR_NORECIPIENT;
	}

	void *parseValue(string arg, MessageEvent& event) const {
		if (Channel::isValidIdentifier(arg)) {
			Channel *channel = Irc::getInstance().findChannel(arg);
			if (channel)
				return channel;
		} else {
			User *user = Irc::getInstance().findUser(arg);
			if (user) 
				return user;
		}
		event.getSender().send(ResponseTypes::ERR_NOSUCHNICK(arg.c_str()));
		return NULL;
	}
};

#endif /* FT_IRC_CORE_MSGTARGET_COMMAND_ELEMENT */
