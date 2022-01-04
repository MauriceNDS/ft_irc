#ifndef FT_IRC_PARSING_COMMAND_ELEMENT
#define FT_IRC_PARSING_COMMAND_ELEMENT

#include <exception>

class CommandElement {
public:
	virtual void *parseValue(const string& arg) = 0;
};

#endif /* FT_IRC_PARSING_COMMAND_ELEMENT */
