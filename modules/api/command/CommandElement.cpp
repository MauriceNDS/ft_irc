#include "api/command/CommandElement.hpp"

bool CommandElement::isRequired() const {
	return true;
}

void *CommandElement::parseValues(list<string> args, MessageEvent& event) const {
	const string& arg = args.front();
	args.pop_front();
	return parseValue(arg, event);
}

void *CommandElement::parseValue(string arg, MessageEvent& event) const {
	(void)arg;
	(void)event;
	return NULL;
}

void CommandElement::destroy(void *) const {}

const ResponseSpec& CommandElement::notProvidedResponse() const {
	return ResponseTypes::ERR_NEEDMOREPARAMS;
}

CommandElement::~CommandElement() {}

CommandElement::Builder::Builder() : _ifNotProvided(&ResponseTypes::ERR_NEEDMOREPARAMS) {}

CommandElement::Builder& CommandElement::Builder::ifNotProvided(const ResponseSpec& response) {
	this->_ifNotProvided = &response;
	return *this;
}

CommandElement::Builder& CommandElement::Builder::element(CommandElement *element) {
	this->_subtype = element;
	return *this;
}

CommandElement *CommandElement::Builder::build() const {
	return new ComplexeCommandElement(_subtype, *_ifNotProvided);
}

ComplexeCommandElement::ComplexeCommandElement(CommandElement *subtype, const ResponseSpec& ifNotProvided) : subtype(subtype), ifNotProvided(ifNotProvided) {}

void *ComplexeCommandElement::parseValues(list<string> args, MessageEvent& event) const {
	return subtype->parseValues(args, event);
}

void *ComplexeCommandElement::parseValue(string arg, MessageEvent& event) const {
	return subtype->parseValue(arg, event);
}

const ResponseSpec& ComplexeCommandElement::notProvidedResponse() const {
	return ifNotProvided;
}

void ComplexeCommandElement::destroy(void *arg) const {
	subtype->destroy(arg);
}

ComplexeCommandElement::~ComplexeCommandElement() {
	delete subtype;
}
