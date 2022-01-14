#include "api/command/CommandSpec.hpp"

void CommandSpec::call(vector<string>& tokens, MessageEvent& event) const {
	map<string, void *const> args;
	vector<string>::iterator tokens_it = tokens.begin();
	vector<pair<string, CommandElement *> >::const_iterator it;

	// Middleware protection
	if (_middleware && !_middleware->handle(event.getSender()))
		return ;

	// Converting string to elements
	for (it = _parameters.begin(); it != _parameters.end() && !event.isCancelled(); it++) {
		string token = "";
		if (tokens_it != tokens.end())
			token = *tokens_it++;
		else if (it->second->isRequired()) {
			event.getSender().send(ERR_NEEDMOREPARAMS);
			event.setCancelled(true);
			break ;
		}
		args.insert(make_pair(it->first, it->second->parseValue(token, event)));
	}

	// Launch command
	if (!event.isCancelled()) {
		event.getSender().send(_executor->execute(Command(_name, args), event.getSender()));
	}

	// Destroy all the created elements
	for (it = _parameters.begin(); it != _parameters.end(); it++) {
		try {
			it->second->destroy(args.at(it->first));
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
