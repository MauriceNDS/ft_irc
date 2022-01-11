#ifndef FT_IRC_API_COMMAND_SPEC
#define FT_IRC_API_COMMAND_SPEC

#include <sstream>

#include "ft_irc.hpp"
#include "api/command/CommandElement.hpp"
#include "api/command/CommandManager.hpp"
#include "api/command/CommandExecutor.hpp"
#include "api/exception/TooFewArgumentsException.hpp"

class CommandManager;

class CommandSpec {
private:
	friend class CommandManager;

	string _name;
	vector<pair<string, CommandElement *> > _parameters;
	CommandExecutor *_executor;

	void call(vector<string>& tokens, User& sender) const {
		map<string, void *const> args;
		vector<string>::iterator tokens_it = tokens.begin();
		vector<pair<string, CommandElement *> >::const_iterator it;

		for (it = _parameters.begin(); it != _parameters.end(); it++) {
			string token = "";
			if (tokens_it != tokens.end())
				token = *tokens_it++;
			if (!it->second->is_valid(token))
				throw TooFewArgumentsException();
			args.insert(make_pair(it->first, it->second->parseValue(token)));
		}

		_executor->execute(Command(_name, args), sender);

		for (it = _parameters.begin(); it != _parameters.end(); it++) {
			it->second->destroy(args.at(it->first));
		}
	}

	CommandSpec(const CommandSpec&);
	CommandSpec& operator=(const CommandSpec&);

protected:
	CommandSpec(const string& name, const vector<pair<string, CommandElement *> >& parameters, CommandExecutor *executor) : _name(name), _parameters(parameters), _executor(executor) {}

public:
	class Builder {
	private:
		string _name;
		vector<pair<string, CommandElement *> > _parameters;
		CommandExecutor *_executor;

	public:
		Builder& name(string name) {
			this->_name = name;
			return *this;
		}

		Builder& argument(string arg, CommandElement *element) {
			this->_parameters.push_back(make_pair(arg, element));
			return *this;
		}

		Builder &executor(CommandExecutor *executor) {
			this->_executor = executor;
			return *this;
		}

		const CommandSpec *build() const {
			return new CommandSpec(_name, _parameters, _executor);
		}
	};

	const string& getName() const {
		return _name;
	}

	~CommandSpec() {
		vector<pair<string, CommandElement *> >::iterator it;
		for (it = _parameters.begin(); it != _parameters.end(); it++) {
			delete it->second;
		}
		delete _executor;
	}
};

#endif /* FT_IRC_API_COMMAND_SPEC */