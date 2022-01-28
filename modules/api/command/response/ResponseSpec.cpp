#include "api/command/response/ResponseSpec.hpp"

string ResponseSpec::operator()(const CommandSender& sender, const char *first, va_list argptr) const {
	string cmd = ":";

	cmd += sender.getName() + " " + _command;
	if (!_args.empty())
		cmd += string(" ") + _args;

	string replacement = first;
	size_t begin = cmd.find("<");
	size_t end = cmd.find(">", begin);
	while (begin != end) {
		cmd.replace(begin, end - begin + 1, replacement);

		begin = cmd.find("<", begin + replacement.length());
		end = cmd.find(">", begin);
		if (begin != end)
			replacement = va_arg(argptr, const char *);
	}
	va_end(argptr);
	return cmd;
}

string ResponseSpec::operator()() const {
	return operator()(Irc::getInstance().getServer());
}

string ResponseSpec::operator()(const char *args...) const {
	std::va_list argptr;
	va_start(argptr, args);

	return operator()(Irc::getInstance().getServer(), args, argptr);
}

string ResponseSpec::operator()(const CommandSender& sender) const {
	string cmd = ":";

	cmd += sender.getName() + " " + _command;
	if (!_args.empty())
		cmd += string(" ") + _args;
	return cmd;
}

string ResponseSpec::operator()(const CommandSender& sender, const char *args...) const {
	std::va_list argptr;
	va_start(argptr, args);

	return operator()(sender, args, argptr);
}
