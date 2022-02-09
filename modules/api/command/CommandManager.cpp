#include "api/command/CommandManager.hpp"
#include "api/ResponseTypes.hpp"

void CommandManager::registerCommand(const CommandSpec *spec) {
	if (!cspecs.insert(make_pair(spec->getName(), spec)).second)
		throw DuplicatedCommandException();
}

void CommandManager::process(MessageEvent& event) {
	list<string> tokens;
	map<string, const CommandSpec *>::iterator it = cspecs.end();

	std::istringstream ss(event.getMessage());
	string command;
	std::getline(ss, command, ' ');

	it = cspecs.find(command);
	if (it == cspecs.end()) {
		event.getSender().send(ResponseTypes::ERR_UNKNOWNCOMMAND(command.c_str()));
		return ;
	}

	bool lastStr = false;
	string temp;
	while (ss >> temp) {
		if (temp[0] == ':') {
			lastStr = true;
			break ;
		}
		tokens.push_back(temp);
	}
	if (lastStr) {
		temp.erase(temp.begin());
		tokens.push_back(temp);
		if (std::getline(ss, temp)) {
			tokens.back() += temp;
		}
	}

	it->second->call(tokens, event);
}

CommandManager::~CommandManager() {
	map<string, const CommandSpec *>::iterator it;
	for (it = cspecs.begin(); it != cspecs.end(); it++) {
		delete it->second;
	}
}
