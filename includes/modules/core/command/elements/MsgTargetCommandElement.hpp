#ifndef FT_IRC_CORE_MSGTARGET_COMMAND_ELEMENT
#define FT_IRC_CORE_MSGTARGET_COMMAND_ELEMENT

#include "ft_irc.hpp"

#include "core/Irc.hpp"

#include "api/User.hpp"
#include "api/Channel.hpp"
#include "api/command/CommandElement.hpp"
#include "api/event/MessageEvent.hpp"

class MsgTargetCommandElement : public CommandElement {
public:
	ResponseType notProvidedResponse() const {
		return ERR_NORECIPIENT;
	}

	void *parseValue(const string& arg, MessageEvent& event) const {
		if (Channel::isValidIdentifier(arg)) {
		} else {
			User *user = Irc::getInstance().findUser(arg);
			if (user) 
				return user;
		}
		// event.getSender().send(ERR_NOSUCHNICK);
		return NULL;
	}
};

#endif /* FT_IRC_CORE_MSGTARGET_COMMAND_ELEMENT */
