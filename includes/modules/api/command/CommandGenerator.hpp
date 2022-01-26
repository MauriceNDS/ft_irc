#ifndef FT_IRC_API_COMMAND_GENERATOR
#define FT_IRC_API_COMMAND_GENERATOR

#include "ft_irc.hpp"

#include "api/ResponseType.hpp"

#include <cstdarg>

class CommandGenerator {
private:
	string _prefix;
	string _name;
	vector<string> arguments;

public:
	CommandGenerator(const string& name, const string& prefix = "") : _prefix(prefix), _name(name) {}

	CommandGenerator(const ResponseType& response, const string& prefix = "") : _prefix(prefix) {
		int numeric = static_cast<int>(response);
		_name = string(3, '0');

		_name[2] = (numeric % 10) + '0';
		numeric /= 10;
		_name[1] = (numeric % 10) + '0';
		numeric /= 10;
		_name[0] = (numeric % 10) + '0';
	}

public:
	void add(const string& arg) {
		arguments.push_back(arg);
	}

	string build() const {
		string result;
		if (!_prefix.empty()) {
			result += ":";
			result += _prefix;
		}
		result += _name;
		for (vector<string>::const_iterator it = arguments.begin(); it < arguments.end(); it++) {
			if (it == arguments.end() - 1)
				result += ":";
			result += *it;
		}
		return result;
	}
};

#endif /* FT_IRC_API_COMMAND_GENERATOR */
