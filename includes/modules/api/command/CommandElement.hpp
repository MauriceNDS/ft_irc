#ifndef FT_IRC_API_COMMAND_ELEMENT
#define FT_IRC_API_COMMAND_ELEMENT

#include <exception>

#include "ft_irc.hpp"

#include "api/event/MessageEvent.hpp"

class CommandElement {
public:
	virtual bool isRequired() {
		return true;
	}

	virtual void *parseValue(const string& arg, MessageEvent& event) const = 0;

	virtual void destroy(void *) const {}
	virtual ~CommandElement() {}
};

#endif /* FT_IRC_API_COMMAND_ELEMENT */
