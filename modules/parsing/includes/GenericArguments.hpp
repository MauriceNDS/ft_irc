#ifndef FT_IRC_PARSING_GENERIC_ARGUMENTS
#define FT_IRC_PARSING_GENERIC_ARGUMENTS

#include <cstdlib>

#include "ft_irc.hpp"

#include "parsing/includes/CommandElement.hpp"

class StringCommandElement : public CommandElement {
private:
	string val;

public:
	void *parseValue(const string& arg) {
		this->val = arg;
		return &this->val;
	}
};

class IntegerCommandElement : public CommandElement {
private:
	int val;

public:
	void *parseValue(const string& arg) {
		this->val = atoi(arg.c_str());
		return &this->val;
	}
};

class GenericArguments {
private:
	GenericArguments();

public:
	static StringCommandElement *string() {
		return new StringCommandElement();
	}

	static IntegerCommandElement *integer() {
		return new IntegerCommandElement();
	}
};

#endif /* FT_IRC_PARSING_GENERIC_ARGUMENTS */
