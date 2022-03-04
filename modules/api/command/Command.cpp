#include "api/command/Command.hpp"

Command::Command(const string& name, map<string, void *const>& args, const CommandSender& sender) : _name(name), _args(args), _sender(sender) {}

const string& Command::getCommand() const {
	return _name;
}

const CommandSender& Command::getSender() const {
	return _sender;
}