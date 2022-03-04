#include "core/command/element/ChannelCommandElement.hpp"

ChannelCommandElement::ChannelCommandElement(bool createIfUnknown) : createIfUnknown(createIfUnknown) {};

void *ChannelCommandElement::parseValue(string arg, MessageEvent& event) const {
	if (Channel::isValidIdentifier(arg)) {
		Channel *channel;
		if ((channel = Irc::getInstance().findChannel(arg))) {
			return (channel);
		} else if (createIfUnknown) {
			channel = new Channel(arg);
			Irc::getInstance().addChannel(channel);
			return (channel);
		}
	}
	event.getSender().send(ResponseTypes::ERR_NOSUCHCHANNEL(arg.c_str()));
	return NULL;
}