#ifndef FT_IRC_API_RESPONSE
#define FT_IRC_API_RESPONSE

#include "api/command/response/ResponseSpec.hpp"

namespace ResponseTypes {
	const ResponseSpec RPL_WELCOME = ResponseSpec(1, ":Welcome to the Internet Relay Network <nick>!<user>@<host>");
	const ResponseSpec RPL_YOURHOST = ResponseSpec(2, ":Your host is <servername>, running version <ver>");
	const ResponseSpec RPL_CREATED = ResponseSpec(3, ":This server was created <date>");
	const ResponseSpec RPL_MYINFO = ResponseSpec(4, "<servername> <version> <available user modes> <available channel modes>");
	const ResponseSpec ERR_NOVALIDPASS = ResponseSpec(503, ":You need a valid PASS command");
	const ResponseSpec RPL_NONE = ResponseSpec(300);
	const ResponseSpec RPL_LIST = ResponseSpec(322, "<channel> # visible :<topic>");
	const ResponseSpec RPL_LISTEND = ResponseSpec(323, ":End of LIST");
	const ResponseSpec RPL_TOPIC = ResponseSpec(332, "<channel> :<topic>");
	const ResponseSpec RPL_NAMREPLY = ResponseSpec(353, "<channel> :<nickname>");
	const ResponseSpec RPL_ENDOFNAMES = ResponseSpec(366, "<channel> :End of NAMES list");
	const ResponseSpec RPL_YOUREOPER = ResponseSpec(381, ":You are now an IRC operator");
	const ResponseSpec ERR_NOSUCHNICK = ResponseSpec(401, "<nickname> :No such nick/channel");
	const ResponseSpec ERR_NOTONCHANNEL = ResponseSpec(442, "<channel> :You're not on that channel");
	const ResponseSpec ERR_NOSUCHCHANNEL = ResponseSpec(403, "<channel name> :No such channel");
	const ResponseSpec ERR_CHANOPRIVSNEEDED = ResponseSpec(482, "<channel> :You're not channel operator");
	const ResponseSpec ERR_NOORIGIN = ResponseSpec(409, ":No origin specified");
	const ResponseSpec ERR_NORECIPIENT = ResponseSpec(411, ":No recipient given (<command>)");
	const ResponseSpec ERR_NOTEXTTOSEND = ResponseSpec(412, ":No text to send");
	const ResponseSpec ERR_UNKNOWNCOMMAND = ResponseSpec(421, "<command> :Unknown command");
	const ResponseSpec ERR_NONICKNAMEGIVEN = ResponseSpec(431, ":No nickname given");
	const ResponseSpec ERR_ERRONEUSNICKNAME = ResponseSpec(432, "<nick> :Erroneous nickname");
	const ResponseSpec ERR_NICKNAMEINUSE = ResponseSpec(433, "<nick> :Nickname is already in use");
	const ResponseSpec ERR_USERNOTINCHANNEL = ResponseSpec(441, "<nick> <channel> :They aren't on that channel");
	const ResponseSpec ERR_NOTREGISTERED = ResponseSpec(451, ":You have not registered");
	const ResponseSpec ERR_NEEDMOREPARAMS = ResponseSpec(461, "<command> :Not enough parameters");
	const ResponseSpec ERR_ALREADYREGISTRED = ResponseSpec(462, ":Unauthorized command (already registered)");
	const ResponseSpec ERR_PASSWDMISMATCH = ResponseSpec(464, ":Password incorrect");
	const ResponseSpec ERR_NOOPERHOST = ResponseSpec(491, ":No O-lines for your host");
};

#endif /* FT_IRC_API_RESPONSE */
