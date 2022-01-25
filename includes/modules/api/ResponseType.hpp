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

class ResponseSpec {

	/**
	 * @brief Creates a response from a template.
	 * 
	 * @param command The command name.
	 * @param args All the arguments as a template. Example: `<nick> :Erroneous nickname'
	 */
	ResponseSpec(const string& command, const string& args) {

	}

	/**
	 * @brief Generates a string representation of the response.
	 * 
	 * @param sender 
	 * @return string 
	 */
	string build(const CommandSender& sender, const string& ...) {
		string command;

		command += ":";
		command += sender.getName();
		command += " ";
		// TODO Get all args from ...
	}
};

#endif /* FT_IRC_API_RESPONSE */
