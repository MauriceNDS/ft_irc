#ifndef FT_IRC_API_USER
#define FT_IRC_API_USER

#include "ft_irc.hpp"

class User {
private:
	string nickName;
	string userName;
	string hostName;
	string serverName;
	string realName;
	bool oper;

public:
	// TODO test
	User(string name) : nickName(name), oper(false) {}

	void setOperator()	{ oper = true; }
	bool isOperator()	{ return oper; }

	void setNickName(const string& nickName)		{ this->nickName = nickName; }
	void setUserName(const string& userName)		{ this->userName = userName; }
	void setHostName(const string& hostName)		{ this->hostName = hostName; }
	void setServerName(const string& serverName)	{ this->serverName = serverName; }
	void setRealName(const string& realName)		{ this->realName = realName; }

	const string& getNickName()		{ return this->nickName; }
	const string& getUserName()		{ return this->userName; }
	const string& getHostName()		{ return this->hostName; }
	const string& getServerName()	{ return this->serverName; }
	const string& getRealName()		{ return this->realName; }
};

#endif /* FT_IRC_API_USER */
