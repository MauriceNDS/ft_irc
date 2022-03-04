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
	const ResponseSpec& notProvidedResponse() const;

	void *parseValue(string arg, MessageEvent& event) const;
};

#endif /* FT_IRC_CORE_MSGTARGET_COMMAND_ELEMENT */
