#include "api/command/CommandManager.hpp"

void CommandManager::registerCommand(const CommandSpec *spec) {
	if (!specs.insert(make_pair(spec->getName(), spec)).second)
		throw DuplicatedCommandException();
}

void CommandManager::post(MessageEvent& event) {
	vector<string> tokens;
	map<string, const CommandSpec *>::iterator it = specs.end();

	std::istringstream ss(event.getMessage());
	string command;
	std::getline(ss, command, ' ');

	it = specs.find(command);
	if (it == specs.end())
		throw CommandNotFoundException();

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
	for (it = specs.begin(); it != specs.end(); it++) {
		delete it->second;
	}
}
