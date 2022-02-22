#include "core/command/PingCommand.hpp"

#include "api/ResponseTypes.hpp"

void PingCommand::execute(const Command& cmd, CommandSender& sender) {
	string& server = cmd.getArg<string>("server");
	sender.send(ResponseTypes::PONG(server.c_str()));
}
