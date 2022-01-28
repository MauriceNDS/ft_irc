#ifndef FT_IRC_CORE_USER_COMMAND_ELEMENT
#define FT_IRC_CORE_USER_COMMAND_ELEMENT

#include "ft_irc.hpp"

#include "api/User.hpp"
#include "api/command/CommandElement.hpp"
#include "api/exception/ArgumentParseException.hpp"
#include "api/event/MessageEvent.hpp"

#include "core/Irc.hpp"

class UserCommandElement : public CommandElement {
public:
	void *parseValue(const string& arg, MessageEvent& event) const {
		User *user = Irc::getInstance().findUser(arg);
		if (user)
			return user;
		// event.getSender().send(ERR_NOSUCHNICK);
		return NULL;
	}
};

#endif /* FT_IRC_CORE_USER_COMMAND_ELEMENT */
