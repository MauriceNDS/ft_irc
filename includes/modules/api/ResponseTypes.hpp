#ifndef FT_IRC_API_RESPONSE
#define FT_IRC_API_RESPONSE

#include "api/command/response/ResponseSpec.hpp"

namespace ResponseTypes {
	const ResponseSpec ERROR = ResponseSpec("ERROR");
	const ResponseSpec PRIVMSG = ResponseSpec("PRIVMSG", "<client> :<message>");
	const ResponseSpec NOTICE = ResponseSpec("NOTICE", "<client> :<message>");
	const ResponseSpec JOIN = ResponseSpec("JOIN", ":<channel>");
	const ResponseSpec KICK = ResponseSpec("KICK", "<channel> :<message>");
	const ResponseSpec PART = ResponseSpec("PART", "<channel> :<message>");
	const ResponseSpec NICK = ResponseSpec("NICK", ":<nick>");
	const ResponseSpec PONG = ResponseSpec("PONG", "<server>");
	const ResponseSpec QUIT = ResponseSpec("QUIT", ":<message>");
	const ResponseSpec MODE = ResponseSpec("MODE", "<channel> <modes>");
	const ResponseSpec RPL_WELCOME = ResponseSpec(1, "<client> :Welcome to the Internet Relay Network <sendername>");
	const ResponseSpec RPL_YOURHOST = ResponseSpec(2, "<client> :Your host is <servername>, running version <ver>");
	const ResponseSpec RPL_CREATED = ResponseSpec(3, "<client> :This server was created <date>");
	const ResponseSpec RPL_MYINFO = ResponseSpec(4, "<client> <servername> <version> <available user modes> <available channel modes>");
	const ResponseSpec RPL_NONE = ResponseSpec(300);
	const ResponseSpec RPL_LIST = ResponseSpec(322, "<client> <channel> <# visible> :<topic>");
	const ResponseSpec RPL_LISTEND = ResponseSpec(323, "<client> :End of LIST");
	const ResponseSpec RPL_CHANNELMODEIS = ResponseSpec(324, "<client> <channel> <mode> <mode params>");
	const ResponseSpec RPL_TOPIC = ResponseSpec(332, "<client> <channel> :<topic>");
	const ResponseSpec RPL_INVITING = ResponseSpec(341, "<client> <nick> <channel>");
	const ResponseSpec RPL_NAMREPLY = ResponseSpec(353, "<client> <symbol> <channel> :<nickname>");
	const ResponseSpec RPL_ENDOFNAMES = ResponseSpec(366, "<client> <channel> :End of NAMES list");
	const ResponseSpec RPL_YOUREOPER = ResponseSpec(381, "<client> :You are now an IRC operator");
	const ResponseSpec ERR_NOSUCHNICK = ResponseSpec(401, "<nickname> :No such nick/channel");
	const ResponseSpec ERR_NOSUCHCHANNEL = ResponseSpec(403, "<channel name> :No such channel");
	const ResponseSpec ERR_CANNOTSENDTOCHAN = ResponseSpec(404, "<channel name> :Cannot send to channel");
	const ResponseSpec ERR_CHANOPRIVSNEEDED = ResponseSpec(482, "<channel> :You're not channel operator");
	const ResponseSpec ERR_NOORIGIN = ResponseSpec(409, ":No origin specified");
	const ResponseSpec ERR_NORECIPIENT = ResponseSpec(411, ":No recipient given (<command>)");
	const ResponseSpec ERR_NOTEXTTOSEND = ResponseSpec(412, ":No text to send");
	const ResponseSpec ERR_UNKNOWNCOMMAND = ResponseSpec(421, "<command> :Unknown command");
	const ResponseSpec ERR_NONICKNAMEGIVEN = ResponseSpec(431, ":No nickname given");
	const ResponseSpec ERR_ERRONEUSNICKNAME = ResponseSpec(432, "<client> <nick> :Erroneous nickname");
	const ResponseSpec ERR_NICKNAMEINUSE = ResponseSpec(433, "<nick> :Nickname is already in use");
	const ResponseSpec ERR_USERNOTINCHANNEL = ResponseSpec(441, "<nick> <channel> :They aren't on that channel");
	const ResponseSpec ERR_NOTONCHANNEL = ResponseSpec(442, "<channel> :You're not on that channel");
	const ResponseSpec ERR_USERONCHANNEL = ResponseSpec(443, "<nick> <channel> :is already on channel");
	const ResponseSpec ERR_NOTREGISTERED = ResponseSpec(451, ":You have not registered");
	const ResponseSpec ERR_NEEDMOREPARAMS = ResponseSpec(461, "<command> :Not enough parameters");
	const ResponseSpec ERR_ALREADYREGISTRED = ResponseSpec(462, ":Unauthorized command (already registered)");
	const ResponseSpec ERR_PASSWDMISMATCH = ResponseSpec(464, "<client> :Password incorrect");
	const ResponseSpec ERR_KEYSET = ResponseSpec(467, "<channel> :Channel key already set");
	const ResponseSpec ERR_CHANNELISFULL = ResponseSpec(471, "<channel> :Cannot join channel (+l)");
	const ResponseSpec ERR_UNKNOWNMODE = ResponseSpec(472, "<char> :is unknown mode");
	const ResponseSpec ERR_INVITEONLYCHAN = ResponseSpec(473, "<channel> :Cannot join channel (+i)");
	const ResponseSpec ERR_BADCHANNELKEY = ResponseSpec(475, "<channel> :Cannot join channel (+k)");
	const ResponseSpec ERR_NOCHANMODES = ResponseSpec(477, "<client> <channel> :Channel doesn't support modes");
	const ResponseSpec ERR_NOPRIVILEGES = ResponseSpec(481, "<client> :Permission Denied- You're not an IRC operator");
	const ResponseSpec ERR_NOOPERHOST = ResponseSpec(491, "<client> :No O-lines for your host");
	const ResponseSpec ERR_NOVALIDPASS = ResponseSpec(503, ":You need a valid PASS command");
}

#endif /* FT_IRC_API_RESPONSE */
