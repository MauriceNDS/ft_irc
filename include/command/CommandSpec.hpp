#ifndef FT_IRC_COMMAND_SPEC
#define FT_IRC_COMMAND_SPEC

#include "core.hpp"
#include "command/CommandElement.hpp"
#include "command/CommandExecutor.hpp"

class CommandSpec {
private:
	string name;
	vector<pair<const string, CommandElement*> > _parameters;
	CommandExecutor *executor;

protected:
	CommandSpec(const string& name, vector<pair<const string, CommandElement*> >& parameters, CommandExecutor *executor) : name(name), executor(executor) {
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

	void call() const {
		executor->execute(Command(), CommandSender());
	}
};

#endif /* FT_IRC_COMMAND_SPEC */
