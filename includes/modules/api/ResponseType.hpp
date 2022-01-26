#ifndef FT_IRC_API_RESPONSE
#define FT_IRC_API_RESPONSE

#include "api/command/CommandSpec.hpp"

enum ResponseType {
	RPL_NONE = 300,
	ERR_NOSUCHNICK = 401,
	ERR_NOSUCHCHANNEL = 403,
	ERR_NORECIPIENT = 411,
	ERR_NOTEXTTOSEND = 412,
	ERR_UNKNOWNCOMMAND = 421,
	ERR_NONICKNAMEGIVEN = 431,
	ERR_ERRONEUSNICKNAME = 432,
	ERR_NICKNAMEINUSE = 433,
	ERR_NICKCOLLISION = 436,
	ERR_NOTREGISTERED = 451,
	ERR_NEEDMOREPARAMS = 461,
	ERR_ALREADYREGISTRED = 462,
};

#include <algorithm>
#include <cstdarg>

class ResponseSpec {
private:
	string _command;
	string _args;

public:
	/**
	 * @brief Creates a response from a template.
	 * 
	 * @param command The command name.
	 * @param args All the arguments as a template. Example: `<nick> :Erroneous nickname'
	 */
	ResponseSpec(const string& command, const string& args) : _command(command), _args(args) {}

	/**
	 * @brief Generates a string representation of the response.
	 * 
	 * @param sender 
	 * @return string 
	 */
	string build(const CommandSender& sender) {
		return build(sender, "");
	}

	/**
	 * @brief Generates a string representation of the response.
	 * 
	 * @param sender 
	 * @param args 
	 * @return string 
	 */
	string build(const CommandSender& sender, const char *args...) {
		string cmd = ":";

		cmd += sender.getName() + " " + _command + " " + _args;

		std::va_list argptr;
    	va_start(argptr, args);

		string replacement = args;
		size_t begin = cmd.find("<");
		size_t end = cmd.find(">", begin);
		while (begin != end) {
			cmd.replace(begin, end - begin + 1, replacement);

			begin = cmd.find("<", begin + replacement.length());
			end = cmd.find(">", begin);
			if (begin != end)
				replacement = va_arg(argptr, char *);
		}
    	va_end(argptr);
		return cmd;
	}
};

#endif /* FT_IRC_API_RESPONSE */
