#ifndef FT_IRC_API_COMMAND_ELEMENT
#define FT_IRC_API_COMMAND_ELEMENT

#include <exception>

#include "ft_irc.hpp"

#include "api/event/MessageEvent.hpp"

template <class T>
class ComplexeCommandElement : public CommandElement {
private:
	map<CommandElement *, bool (*)(const string&)> subtypes;

	ComplexeCommandElement(CommandElement *subtype) : subtype(subtype) {}
public:
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

	~ComplexeCommandElement() {
		delete this->subtype;
	}
};

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
