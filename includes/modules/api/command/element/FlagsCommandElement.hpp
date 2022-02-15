#ifndef FT_IRC_API_FLAGS_COMMAND_ELEMENT
#define FT_IRC_API_FLAGS_COMMAND_ELEMENT

#include "ft_irc.hpp"

#include "core/Irc.hpp"

#include "api/ResponseTypes.hpp"
#include "api/Flag.hpp"
#include "api/User.hpp"
#include "api/Channel.hpp"
#include "api/command/CommandElement.hpp"
#include "api/event/MessageEvent.hpp"

class FlagsCommandElement : public CommandElement {
private:
	string flags;

public:
	FlagsCommandElement(const string& flags);

	void *parseValues(list<string>& args, MessageEvent& event) const;

	void destroy(void *arg) const;
};

#endif /* FT_IRC_API_FLAGS_COMMAND_ELEMENT */
