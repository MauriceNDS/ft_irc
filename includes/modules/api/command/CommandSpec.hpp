#ifndef FT_IRC_API_COMMAND_SPEC
#define FT_IRC_API_COMMAND_SPEC

#include <sstream>

#include "ft_irc.hpp"
#include "api/command/CommandElement.hpp"
#include "api/command/CommandManager.hpp"
#include "api/command/CommandExecutor.hpp"
#include "api/exception/TooFewArgumentsException.hpp"
#include "api/middleware/Middleware.hpp"

class CommandManager;
class CommandExecutor;

class CommandSpec {
private:
	friend class CommandManager;

	string _name;
	vector<pair<string, CommandElement *> > _parameters;
	CommandExecutor *_executor;
	Middleware *_middleware;

	void call(vector<string>& tokens, MessageEvent& event) const;

	CommandSpec(const CommandSpec&);
	CommandSpec& operator=(const CommandSpec&);

protected:
	CommandSpec(const string& name, const vector<pair<string, CommandElement *> >& parameters, CommandExecutor *executor, Middleware *middleware) : _name(name), _parameters(parameters), _executor(executor), _middleware(middleware) {}

public:
	class Builder {
	private:
		string _name;
		vector<pair<string, CommandElement *> > _parameters;
		CommandExecutor *_executor;
		Middleware *_middleware;

	public:
		Builder() : _executor(nullptr), _middleware(nullptr) {}

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

		Builder &middleware(Middleware *middleware) {
			this->_middleware = middleware;
			return *this;
		}

		const CommandSpec *build() const {
			return new CommandSpec(_name, _parameters, _executor, _middleware);
		}
	};

	const string& getName() const {
		return _name;
	}

	~CommandSpec();
};

#endif /* FT_IRC_API_COMMAND_SPEC */
