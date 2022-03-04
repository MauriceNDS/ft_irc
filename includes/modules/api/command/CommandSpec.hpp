#ifndef FT_IRC_API_COMMAND_SPEC
#define FT_IRC_API_COMMAND_SPEC

#include <sstream>

#include "ft_irc.hpp"
#include "api/event/MessageEvent.hpp"

class Middleware;
class CommandManager;
class CommandExecutor;
class CommandElement;

#include "api/middleware/Middleware.hpp"
#include "api/command/CommandManager.hpp"
#include "api/command/CommandExecutor.hpp"
#include "api/command/CommandElement.hpp"

class CommandSpec {
private:
	friend class CommandManager;

	string _name;
	vector<pair<string, CommandElement *> > _parameters;
	CommandExecutor *_executor;
	Middleware *_middleware;

	void call(list<string>& tokens, MessageEvent& event) const;

	CommandSpec(const CommandSpec&);
	CommandSpec& operator=(const CommandSpec&);

protected:
	CommandSpec(const string& name, const vector<pair<string, CommandElement *> >& parameters, CommandExecutor *executor, Middleware *middleware);

public:
	class Builder {
	private:
		string _name;
		vector<pair<string, CommandElement *> > _parameters;
		CommandExecutor *_executor;
		Middleware *_middleware;

	public:
		Builder();

		Builder& name(string name);

		Builder& argument(string arg, CommandElement *element);

		Builder &executor(CommandExecutor *executor);

		Builder &middleware(Middleware *middleware);

		const CommandSpec *build() const;
	};

	const string& getName() const;

	~CommandSpec();
};

#endif /* FT_IRC_API_COMMAND_SPEC */
