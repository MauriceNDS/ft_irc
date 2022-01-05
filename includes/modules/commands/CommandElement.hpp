#ifndef FT_IRC_PARSING_COMMAND_ELEMENT
#define FT_IRC_PARSING_COMMAND_ELEMENT

#include <exception>

class CommandElement {
public:
	virtual bool is_valid(const string& arg) {
		return !arg.empty();
	}

	virtual void *parseValue(const string& arg) const = 0;

	virtual void destroy(void *) const {}
	virtual ~CommandElement() {}
};

#endif /* FT_IRC_PARSING_COMMAND_ELEMENT */
