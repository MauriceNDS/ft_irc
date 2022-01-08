#ifndef FT_IRC_COMMANDS_GENERIC_ARGUMENTS
#define FT_IRC_COMMANDS_GENERIC_ARGUMENTS

#include <cstdlib>
#include <sstream>

#include "ft_irc.hpp"

#include "commands/CommandElement.hpp"

class StringCommandElement : public CommandElement {
public:
	void *parseValue(const string& arg) const {
		return new string(arg);
	}

	void destroy(void *arg) const {
		delete static_cast<string*>(arg);
	}
};

class IntegerCommandElement : public CommandElement {
public:
	void *parseValue(const string& arg) const {
		return new int(atoi(arg.c_str()));
	}

	void destroy(void *arg) const {
		delete static_cast<int*>(arg);
	}
};

class OptionalCommandElement : public CommandElement {
private:
	CommandElement *subtype;

	OptionalCommandElement();
public:
	OptionalCommandElement(CommandElement *subtype) : subtype(subtype) {}

	bool is_valid(const string& arg) {
		(void)arg;
		return true;
	}

	void *parseValue(const string& arg) const {
		if (arg.empty())
			return new const void*(nullptr);
		return new const void*(subtype->parseValue(arg));
	}

	void destroy(void *arg) const {
		delete static_cast<void **>(arg);
	}

	~OptionalCommandElement() {
		delete this->subtype;
	}
};

template <class T>
class ListCommandElement : public CommandElement {
private:
	CommandElement *subtype;

	ListCommandElement();
public:
	ListCommandElement(CommandElement *subtype) : subtype(subtype) {}

	void *parseValue(const string& arg) const {
		vector<T*> *val = new vector<T*>();

		string cpy = arg;
		std::replace(cpy.begin(), cpy.end(), ',', ' ');

		vector<string> tokens;
		std::stringstream ss(cpy);
		string temp;
		while (ss >> temp)
			tokens.push_back(temp);
		vector<string>::iterator tokens_it;

		for (tokens_it = tokens.begin(); tokens_it != tokens.end(); tokens_it++) {
			val->push_back(static_cast<T*>(subtype->parseValue(*tokens_it)));
		}
		return val;
	}

	void destroy(void *arg) const {
		vector<T*>* base = static_cast<vector<T*>* >(arg);

		typename vector<T*>::const_iterator it = base->begin();
		while (it != base->end())
			subtype->destroy(*it++);
		delete base;
	}

	~ListCommandElement() {
		delete this->subtype;
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

	template <class T>
	static ListCommandElement<T> *list(CommandElement *subtype) {
		return new ListCommandElement<T>(subtype);
	}
};

#endif /* FT_IRC_COMMANDS_GENERIC_ARGUMENTS */
