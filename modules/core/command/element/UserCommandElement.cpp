#include "core/command/element/UserCommandElement.hpp"

void *UserCommandElement::parseValue(string arg, MessageEvent& event) const {
	User *user = Irc::getInstance().findUser(arg);
	if (user)
		return user;
	event.getSender().send(ResponseTypes::ERR_NOSUCHNICK(arg.c_str()));
	return NULL;
}