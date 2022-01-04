#ifndef FT_IRC_PARSING_COMMAND
#define FT_IRC_PARSING_COMMAND

#include "parsing/includes/CommandSpec.hpp"
#include "parsing/includes/CommandElement.hpp"
#include "parsing/includes/exception/ArgumentNotFoundException.hpp"

class Command {
private:
	friend class CommandSpec;

	string _name;
	map<string, void*>& _args;

	Command(const string& name, map<string, void*>& args) : _name(name), _args(args) {}

public:
	template <class T>
	T &getArg(const string& name) {
		T *arg;
		try {
			arg = static_cast<T*>(_args.at(name));
		} catch(const std::out_of_range& e) {
			throw ArgumentNotFoundException();
		}
		return static_cast<T&>(*arg);
	}
};

#endif /* FT_IRC_PARSING_COMMAND */
