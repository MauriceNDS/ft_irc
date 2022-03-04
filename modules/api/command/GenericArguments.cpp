#include "api/command/GenericArguments.hpp"

void * StringCommandElement::parseValue(string arg, MessageEvent& event) const {
	(void)event;
	return new string(arg);
}

void StringCommandElement::destroy(void *arg) const {
	delete static_cast<string*>(arg);
}

OptionalCommandElement::OptionalCommandElement(CommandElement *subtype) : subtype(subtype) {}

bool OptionalCommandElement::isRequired() const {
	return false;
}

void *OptionalCommandElement::parseValues(list<string>& args, MessageEvent& event) const {
	if (args.empty())
		return new const void*(NULL);
	void *val = subtype->parseValues(args, event);
	if (!val)
		return NULL;
	return new const void*(val);
}

void *OptionalCommandElement::parseValue(string arg, MessageEvent& event) const {
	if (arg.empty())
		return new const void*(NULL);
	void *val = subtype->parseValue(arg, event);
	if (!val)
		return NULL;
	return new const void*(val);
}

void OptionalCommandElement::destroy(void *arg) const {
	void **elem = static_cast<void **>(arg);
	if (*elem)
		subtype->destroy(*elem);
	delete elem;
}

OptionalCommandElement::~OptionalCommandElement() {
	delete this->subtype;
}

StringCommandElement *GenericArguments::string() {
	return new StringCommandElement();
}

OptionalCommandElement *GenericArguments::optional(CommandElement *subtype) {
	return new OptionalCommandElement(subtype);
}