#ifndef FT_IRC_CORE_USER_COMMAND_ELEMENT
#define FT_IRC_CORE_USER_COMMAND_ELEMENT

#include "ft_irc.hpp"

#include "core/includes/interface/User.hpp"

#include "parsing/includes/CommandElement.hpp"

// TODO test
User global_user("meuh");

class UserCommandElement : public CommandElement {
public:
	void *parseValue(const string& arg) {
		(void)arg;
		return &global_user;
	}
};

#endif /* FT_IRC_CORE_USER_COMMAND_ELEMENT */
