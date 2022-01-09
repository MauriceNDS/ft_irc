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
		try {
			return *static_cast<T*>(_args.at(name));
		} catch(const std::out_of_range& e) {
			throw ArgumentNotFoundException();
		}
	}
};

#endif /* FT_IRC_API_COMMAND */
