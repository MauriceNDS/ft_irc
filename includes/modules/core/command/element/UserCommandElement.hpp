#ifndef FT_IRC_CORE_USER_COMMAND_ELEMENT
#define FT_IRC_CORE_USER_COMMAND_ELEMENT

#include "ft_irc.hpp"

#include "api/User.hpp"
#include "api/command/CommandElement.hpp"
#include "api/event/MessageEvent.hpp"

#include "core/Irc.hpp"

class UserCommandElement : public CommandElement {
public:
	void *parseValue(string arg, MessageEvent& event) const;
};

#endif /* FT_IRC_CORE_USER_COMMAND_ELEMENT */
