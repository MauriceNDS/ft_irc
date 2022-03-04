#include "core/command/element/MsgToCommandElement.hpp"

const ResponseSpec& MsgToCommandElement::notProvidedResponse() const {
	return ResponseTypes::ERR_NORECIPIENT;
}

void *MsgToCommandElement::parseValue(string arg, MessageEvent& event) const {
	if (Channel::isValidIdentifier(arg)) {
		Channel *channel = Irc::getInstance().findChannel(arg);
		if (channel)
			return channel;
	} else {
		User *user = Irc::getInstance().findUser(arg);
		if (user) 
			return user;
	}
	event.getSender().send(ResponseTypes::ERR_NOSUCHNICK(arg.c_str()));
	return NULL;
}