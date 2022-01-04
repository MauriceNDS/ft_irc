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

class OptionalCommandElement : public CommandElement {
private:
	CommandElement *subtype;
	void *empty;
	void *val;

	OptionalCommandElement();
public:
	OptionalCommandElement(CommandElement *subtype) : subtype(subtype), empty(nullptr) {}

	bool is_valid(const string& arg) {
		(void)arg;
		return true;
	}

	void *parseValue(const string& arg) {
		if (arg.empty())
			return &empty;
		this->val = subtype->parseValue(arg);
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

	static OptionalCommandElement *optional(CommandElement *subtype) {
		return new OptionalCommandElement(subtype);
	}
};

#endif /* FT_IRC_PARSING_GENERIC_ARGUMENTS */
