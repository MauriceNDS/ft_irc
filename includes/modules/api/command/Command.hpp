#ifndef FT_IRC_API_COMMAND
#define FT_IRC_API_COMMAND

#include "api/interface/CommandSender.hpp"
#include "api/exception/ArgumentNotFoundException.hpp"

class CommandSpec;

class Command {
private:
	friend class CommandSpec;

	const string _name;
	map<string, void *const> _args;
	const CommandSender& _sender;

	Command(const string& name, map<string, void *const>& args, const CommandSender& sender) : _name(name), _args(args), _sender(sender) {}

public:
	template <class T>
	T &getArg(const string& name) const {
		map<string, void *const>::const_iterator arg = _args.find(name);
		if (arg != _args.end()) {
			return *static_cast<T*>(arg->second);
		} else {
			throw ArgumentNotFoundException();
		}
	}

	const string& getCommand() const {
		return _name;
	}

	const CommandSender& getSender() const {
		return _sender;
	}
};

#endif /* FT_IRC_API_COMMAND */
