#ifndef FT_IRC_CORE_USER_COMMAND_ELEMENT
#define FT_IRC_CORE_USER_COMMAND_ELEMENT

#include "ft_irc.hpp"
#include "command/CommandElement.hpp"

// TODO test
User global_user("meuh");

class UserCommandElement : public CommandElement {
public:
	void *parseValue(const string& arg) {
		return &global_user;
	}
};

#endif /* FT_IRC_CORE_USER_COMMAND_ELEMENT */
