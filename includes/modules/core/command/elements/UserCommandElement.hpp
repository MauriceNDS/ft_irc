#ifndef FT_IRC_CORE_USER_COMMAND_ELEMENT
#define FT_IRC_CORE_USER_COMMAND_ELEMENT

#include "ft_irc.hpp"

#include "api/User.hpp"

#include "api/command/CommandElement.hpp"

#include "api/exception/ArgumentParseException.hpp"

// TODO test
User global_user("meuh");

class UserCommandElement : public CommandElement {
public:
	void *parseValue(const string& arg) const {
		if (arg == "NotAUser" || arg == "NAU")
			throw ArgumentParseException(string(arg) + " is not a user");
		return &global_user;
	}
};

#endif /* FT_IRC_CORE_USER_COMMAND_ELEMENT */
