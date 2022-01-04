#ifndef FT_IRC_PARSING_COMMAND_SPEC
#define FT_IRC_PARSING_COMMAND_SPEC

#include <sstream>

#include "ft_irc.hpp"
#include "parsing/includes/CommandElement.hpp"
#include "parsing/includes/CommandExecutor.hpp"
#include "parsing/includes/exception/TooFewArgumentsException.hpp"

class CommandSpec {
private:
	string _name;
	vector<pair<const string, CommandElement*> > _parameters;
	CommandExecutor *_executor;

protected:
	CommandSpec(const string& name, vector<pair<const string, CommandElement*> >& parameters, CommandExecutor *executor) : _name(name), _executor(executor) {
		this->_parameters.swap(parameters);
	}

public:
	class Builder {
	private:
		string _name;
		vector<pair<const string, CommandElement*> > _parameters;
		CommandExecutor *_executor;

	public:
		Builder& name(string name) {
			this->_name = name;
			return *this;
		}

		Builder& argument(string arg, CommandElement* element) {
			this->_parameters.push_back(make_pair(arg, element));
			return *this;
		}

		Builder &executor(CommandExecutor *executor) {
			this->_executor = executor;
			return *this;
		}

		const CommandSpec build() {
			return CommandSpec(_name, _parameters, _executor);
		}
	};

	void call(string input) const {
		map<string, void*> args;

		vector<string> tokens;
		std::stringstream ss(input);
		string temp;
		while (ss >> temp)
			tokens.push_back(temp);
		vector<string>::iterator tokens_it = tokens.begin();

		vector<pair<const string, CommandElement*> >::const_iterator it;
		for (it = _parameters.begin(); it != _parameters.end(); it++) {
			string token = "";
			if (tokens_it != tokens.end())
				token = *tokens_it++;
			if (!it->second->is_valid(token))
				throw TooFewArgumentsException();
			args[it->first] = it->second->parseValue(token);
		}

		_executor->execute(Command(_name, args), CommandSender());
	}
};

#endif /* FT_IRC_PARSING_COMMAND_SPEC */
