#ifndef FT_IRC_API_GENERIC_ARGUMENTS
#define FT_IRC_API_GENERIC_ARGUMENTS

#include <cstdlib>
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

	bool isRequired() const {
		return false;
	}

	void *parseValue(const string& arg, MessageEvent& event) const {
		if (arg.empty())
			return new const void*(NULL);
		void *val = subtype->parseValue(arg, event);
		if (!val)
			return NULL;
		return new const void*(val);
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
	StringCommandElement *string() {
		return new StringCommandElement();
	}

	// IntegerCommandElement *integer() {
	// 	return new IntegerCommandElement();
	// }

	OptionalCommandElement *optional(CommandElement *subtype) {
		return new OptionalCommandElement(subtype);
	}

	template <class T>
	ListCommandElement<T> *list(CommandElement *subtype) {
		return new ListCommandElement<T>(subtype);
	}
}

#endif /* FT_IRC_API_GENERIC_ARGUMENTS */
