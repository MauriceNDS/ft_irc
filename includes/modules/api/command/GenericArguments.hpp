#ifndef FT_IRC_API_GENERIC_ARGUMENTS
#define FT_IRC_API_GENERIC_ARGUMENTS

#include <cstdlib>
#include <sstream>

#include "ft_irc.hpp"

#include "api/command/CommandElement.hpp"

class StringCommandElement : public CommandElement {
public:
	void *parseValue(string arg, MessageEvent& event) const;

	void destroy(void *arg) const;
};

class OptionalCommandElement : public CommandElement {
private:
	CommandElement *subtype;

	OptionalCommandElement();
public:
	OptionalCommandElement(CommandElement *subtype);

	bool isRequired() const;

	void *parseValues(list<string>& args, MessageEvent& event) const;

	void *parseValue(string arg, MessageEvent& event) const;

	void destroy(void *arg) const;

	~OptionalCommandElement();
};

template <class T>
class ListCommandElement : public CommandElement {
private:
	CommandElement *subtype;

	ListCommandElement();
public:
	ListCommandElement(CommandElement *subtype) : subtype(subtype) {}

	void *parseValue(string arg, MessageEvent& event) const {
		vector<T *> *args = new vector<T *>();
		vector<string> tokens;
		vector<string>::iterator tokens_it;

		std::istringstream ss(arg);
		string temp;
		while (std::getline(ss, temp, ','))
			tokens.push_back(temp);

		for (tokens_it = tokens.begin(); tokens_it != tokens.end(); tokens_it++) {
			void *val = subtype->parseValue(*tokens_it, event);
			if (val)
				args->push_back(static_cast<T *>(val));
		}
		if (args->size() != tokens.size()) {
			destroy(args);
			return NULL;
		}
		return args;
	}

	void destroy(void *arg) const {
		vector<T *> *base = static_cast<vector<T *> *>(arg);

		typename vector<T *>::const_iterator it = base->begin();
		while (it != base->end())
			subtype->destroy(*it++);
		delete base;
	}

	~ListCommandElement() {
		delete this->subtype;
	}
};

namespace GenericArguments {
	StringCommandElement *string();

	OptionalCommandElement *optional(CommandElement *subtype);

	template <class T>
	ListCommandElement<T> *list(CommandElement *subtype) {
		return new ListCommandElement<T>(subtype);
	}
}

#endif /* FT_IRC_API_GENERIC_ARGUMENTS */
