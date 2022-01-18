#ifndef FT_IRC_API_COMMAND
#define FT_IRC_API_COMMAND

#include "api/command/CommandSpec.hpp"
#include "api/exception/ArgumentNotFoundException.hpp"

class Command {
private:
	friend class CommandSpec;

	string _name;
	map<string, void *const> _args;

	Command(const string& name, map<string, void *const>& args) : _name(name), _args(args) {}

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
};

#endif /* FT_IRC_API_COMMAND */
