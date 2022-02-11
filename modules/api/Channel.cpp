#include "api/Channel.hpp"

#include "core/Irc.hpp"

string Channel::getSenderName() const {
	return Irc::getInstance().getServer().getSenderName();
}
