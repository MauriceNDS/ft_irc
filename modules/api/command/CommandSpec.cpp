#include "api/middleware/Middleware.hpp"
#include "api/command/CommandSpec.hpp"
#include "api/command/CommandElement.hpp"
#include "api/command/CommandExecutor.hpp"

void CommandSpec::call(vector<string>& tokens, MessageEvent& event) const {
	map<string, void *const> args;
	vector<string>::iterator tokens_it = tokens.begin();
	vector<pair<string, CommandElement *> >::const_iterator it;

	// Middleware protection
	if (_middleware && !_middleware->handle(event.getSender()))
		return;

	// Converting string to elements
	for (it = _parameters.begin(); it != _parameters.end() && !event.isCancelled(); it++) {
		string token = "";
		if (tokens_it != tokens.end())
			token = *tokens_it++;
		else if (it->second->isRequired()) {
			event.getSender().send(it->second->notProvidedResponse()(getName().c_str()));
			event.setCancelled(true);
			break ;
		}
		void *value = it->second->parseValue(token, event);
		if (value)
			args.insert(make_pair(it->first, value));
		else {
			event.setCancelled(true);
			break ;
		}
	}

	// Launch command
	if (!event.isCancelled()) {
		_executor->execute(Command(_name, args, event.getSender()), event.getSender());
	}

	// Destroy all the created elements
	for (it = _parameters.begin(); it != _parameters.end(); it++) {
		try {
			void *arg = args.at(it->first);
			if (arg)
				it->second->destroy(arg);
		} catch (const std::out_of_range& e) {}
	}
}

CommandSpec::~CommandSpec() {
	vector<pair<string, CommandElement *> >::iterator it;
	for (it = _parameters.begin(); it != _parameters.end(); it++) {
		delete it->second;
	}
	delete _executor;
	delete _middleware;
}
