#ifndef FT_IRC_API_RESPONSE
#define FT_IRC_API_RESPONSE

#include "api/command/response/ResponseSpec.hpp"

namespace ResponseTypes {
	const ResponseSpec RPL_NONE = ResponseSpec(300);
	const ResponseSpec RPL_NAMREPLY = ResponseSpec(353, "<channel> :<nickname>");
	const ResponseSpec RPL_TOPIC = ResponseSpec(332, "<channel> :<topic>");
	const ResponseSpec ERR_NOSUCHNICK = ResponseSpec(401, "<nickname> :No such nick/channel");
	const ResponseSpec ERR_NOTONCHANNEL = ResponseSpec(442, "<channel> :You're not on that channel");
	const ResponseSpec ERR_NOSUCHCHANNEL = ResponseSpec(403, "<channel name> :No such channel");
	const ResponseSpec ERR_CHANOPRIVSNEEDED = ResponseSpec(482, "<channel> :You're not channel operator");
	const ResponseSpec ERR_NORECIPIENT = ResponseSpec(411, ":No recipient given (<command>)");
	const ResponseSpec ERR_NOTEXTTOSEND = ResponseSpec(412, ":No text to send");
	const ResponseSpec ERR_UNKNOWNCOMMAND = ResponseSpec(421, "<command> :Unknown command");
	const ResponseSpec ERR_NONICKNAMEGIVEN = ResponseSpec(431, ":No nickname given");
	const ResponseSpec ERR_ERRONEUSNICKNAME = ResponseSpec(432, "<nick> :Erroneous nickname");
	const ResponseSpec ERR_NICKNAMEINUSE = ResponseSpec(433, "<nick> :Nickname is already in use");
	const ResponseSpec ERR_NOTREGISTERED = ResponseSpec(451, ":You have not registered");
	const ResponseSpec ERR_NEEDMOREPARAMS = ResponseSpec(461, "<command> :Not enough parameters");
	const ResponseSpec ERR_ALREADYREGISTRED = ResponseSpec(462, ":Unauthorized command (already registered)");
};














#endif /* FT_IRC_API_RESPONSE */
