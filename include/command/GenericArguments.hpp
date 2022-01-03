#ifndef FT_IRC_GENERIC_ARGUMENTS
#define FT_IRC_GENERIC_ARGUMENTS

#include <cstdlib>

#include "core.hpp"
#include "CommandElement.hpp"

class StringCommandElement : public CommandElement {
private:
	string val;

public:
	operator string() {
		return val;
	}

	void *parseValue(const string& arg) {
		this->val = arg;
		return this;
	}
};

class IntegerCommandElement : public CommandElement {
private:
	int val;

public:
	// TODO virtual ?
	operator int() {
		return val;
	}

	void *parseValue(const string& arg) {
		this->val = atoi(arg.c_str());
		return this;
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

#endif /* FT_IRC_GENERIC_ARGUMENTS */
