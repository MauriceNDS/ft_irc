#ifndef FT_IRC_API_GENERIC_ARGUMENTS
#define FT_IRC_API_GENERIC_ARGUMENTS

// #include <cstdlib>
#include <sstream>

#include "ft_irc.hpp"

#include "api/command/CommandElement.hpp"

class StringCommandElement : public CommandElement {
public:
	void *parseValue(const string& arg, MessageEvent& event) const {
		(void)event;
		return new string(arg);
	}

	void destroy(void *arg) const {
		delete static_cast<string*>(arg);
	}
};

class IntegerCommandElement : public CommandElement {
public:
	void *parseValue(const string& arg, MessageEvent& event) const {
		(void)event;
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

	bool isRequired() {
		return false;
	}

	void *parseValue(const string& arg, MessageEvent& event) const {
		if (arg.empty())
			return new const void*(nullptr);
		return new const void*(subtype->parseValue(arg, event));
	}

	void destroy(void *arg) const {
		subtype->destroy(*static_cast<void **>(arg));
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

	void *parseValue(const string& arg, MessageEvent& event) const {
		vector<T*> *val = new vector<T*>();
		vector<string> tokens;
		vector<string>::iterator tokens_it;

		std::istringstream ss(arg);
		string temp;
		while (std::getline(ss, temp, ','))
			tokens.push_back(temp);

		for (tokens_it = tokens.begin(); tokens_it != tokens.end(); tokens_it++) {
			val->push_back(static_cast<T*>(subtype->parseValue(*tokens_it, event)));
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

namespace GenericArguments {
	static StringCommandElement *string() {
		return new StringCommandElement();
	}

	// static IntegerCommandElement *integer() {
	// 	return new IntegerCommandElement();
	// }

	// static OptionalCommandElement *optional(CommandElement *subtype) {
	// 	return new OptionalCommandElement(subtype);
	// }

	template <class T>
	static ListCommandElement<T> *list(CommandElement *subtype) {
		return new ListCommandElement<T>(subtype);
	}
};

#endif /* FT_IRC_API_GENERIC_ARGUMENTS */
