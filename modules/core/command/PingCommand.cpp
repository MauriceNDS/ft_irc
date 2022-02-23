#include "core/command/PingCommand.hpp"

void PingCommand::execute(const Command& cmd, CommandSender& sender) {
	string& server = cmd.getArg<string>("server");
	sender.send(ResponseTypes::PONG(server.c_str()));
}
