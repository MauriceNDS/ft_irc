#ifndef FT_IRC_API_RESPONSE_SPEC
#define FT_IRC_API_RESPONSE_SPEC

#include "ft_irc.hpp"
#include "api/interface/CommandSender.hpp"

#include <algorithm>
#include <cstdarg>
#include <sstream>

class ResponseSpec {
private:
	string _command;
	string _args;

	class AnonymousSender : public CommandSender {
	private:
		string name;

	public:
		AnonymousSender() : name("anonymous") {}

		void send(const string& message) const {
			(void)message;
		}

		const string& getName() const {
			return name;
		}

		string getSenderName() const {
			return name;
		}
	};

	string build(const CommandSender& sender, const char *first, va_list argptr) const;

public:
	ResponseSpec(int response, const string& args = "") : _args(args) {
		_command = string(3, '0');

		_command[2] = (response % 10) + '0';
		response /= 10;
		_command[1] = (response % 10) + '0';
		response /= 10;
		_command[0] = (response % 10) + '0';
	}

	ResponseSpec(const string& command, const string& args = "") : _command(command), _args(args) {}

	string operator()() const;
	string operator()(const char *args...) const;
	string operator()(const CommandSender& sender) const;
	string operator()(const CommandSender& sender, const char *args...) const;

	string anonymous() const;
	string anonymous(const char *args...) const;
};

#endif /* FT_IRC_API_RESPONSE_SPEC */
