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

void registerResponseTemplate(ResponseType type, const string& str) {
	CommandSpec::Builder spec = CommandSpec::Builder();
	
	
}

#endif /* FT_IRC_API_RESPONSE */
