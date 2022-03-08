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
		AnonymousSender();

		void send(const string& message) const;

		string getName() const;

		string getSenderName() const;
	};

	string build(const CommandSender& sender, const char *first, va_list argptr) const;

public:
	ResponseSpec(int response, const string& args = "");

	ResponseSpec(const string& command, const string& args = "");

	string operator()() const;
	string operator()(const char *args...) const;
	string operator()(const CommandSender& sender) const;
	string operator()(const CommandSender& sender, const char *args...) const;

	string anonymous() const;
	string anonymous(const char *args...) const;
};

#endif /* FT_IRC_API_RESPONSE_SPEC */
