#include "core/command/SquitCommand.hpp"

#include "core/Irc.hpp"

#include "api/User.hpp"
#include "api/ResponseTypes.hpp"

void SquitCommand::execute(const Command&, CommandSender&) {
	Irc::getInstance().getServer().stop();
}
