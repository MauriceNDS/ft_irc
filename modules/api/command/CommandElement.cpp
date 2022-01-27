#include "api/command/CommandElement.hpp"

bool CommandElement::isRequired() const {
	return true;
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

void *ComplexeCommandElement::parseValue(const string& arg, MessageEvent& event) const {
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
