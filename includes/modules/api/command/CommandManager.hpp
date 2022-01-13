#ifndef FT_IRC_API_COMMAND_MANAGER
#define FT_IRC_API_COMMAND_MANAGER

#include "ft_irc.hpp"

#include "server/Response.hpp"

#include "api/User.hpp"
#include "api/command/CommandSpec.hpp"
#include "api/event/MessageEvent.hpp"

#include "api/exception/CommandNotFoundException.hpp"
#include "api/exception/DuplicatedCommandException.hpp"

class CommandSpec;

class CommandManager {
private:
	map<string, const CommandSpec *> specs;

public:
	void registerCommand(const CommandSpec *spec) {
		if (!specs.insert(make_pair(spec->getName(), spec)).second)
			throw DuplicatedCommandException();
	}

	void post(MessageEvent& event) {
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

	~CommandManager() {
		map<string, const CommandSpec *>::iterator it;
		for (it = specs.begin(); it != specs.end(); it++) {
			delete it->second;
		}
	}
};

#endif /* FT_IRC_API_COMMAND_MANAGER */
