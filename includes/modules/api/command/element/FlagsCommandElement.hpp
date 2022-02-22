#ifndef FT_IRC_API_FLAGS_COMMAND_ELEMENT
#define FT_IRC_API_FLAGS_COMMAND_ELEMENT

#include "ft_irc.hpp"

#include "api/event/MessageEvent.hpp"
#include "api/command/CommandElement.hpp"

class FlagsCommandElement : public CommandElement {
private:
	string flags;

public:
	FlagsCommandElement(const string& flags);

	void *parseValues(list<string>& args, MessageEvent& event) const;

	void destroy(void *arg) const;
};

#endif /* FT_IRC_API_FLAGS_COMMAND_ELEMENT */
