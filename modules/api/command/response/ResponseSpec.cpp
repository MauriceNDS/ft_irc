#include "api/command/response/ResponseSpec.hpp"

#include "core/Irc.hpp"

string ResponseSpec::build(const CommandSender& sender, const char *first, va_list argptr) const {
	string cmd = ":";

	cmd += sender.getSenderName() + " " + _command;
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
	cmd += "\n";
	return cmd;
}

string ResponseSpec::operator()() const {
	return operator()(Irc::getInstance().getServer());
}

string ResponseSpec::operator()(const char *args...) const {
	std::va_list argptr;
	va_start(argptr, args);

	return build(Irc::getInstance().getServer(), args, argptr);
}

string ResponseSpec::operator()(const CommandSender& sender) const {
	string cmd = ":";

	cmd += sender.getSenderName() + " " + _command;
	if (!_args.empty())
		cmd += string(" ") + _args;
	cmd += "\n";
	return cmd;
}

string ResponseSpec::operator()(const CommandSender& sender, const char *args...) const {
	std::va_list argptr;
	va_start(argptr, args);

	return build(sender, args, argptr);
}

string ResponseSpec::anonymous() const {
	return operator()(ResponseSpec::AnonymousSender());
}

string ResponseSpec::anonymous(const char *args...) const {
	std::va_list argptr;
	va_start(argptr, args);

	return build(ResponseSpec::AnonymousSender(), args, argptr);
}
