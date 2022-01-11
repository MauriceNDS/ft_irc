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

	void setOperator() {oper = true;}
	bool isOperator() {return oper;}

	void setUserName(string & username) {userName = username;}
	void setHostName(string & hostname) {hostName = hostname;}
	void setServerName(string & servername) {serverName = servername;}
	void setRealName(string & realname) {realName = realname;}
	string & getUserName(string & username) {return userName;}
	string & getHostName(string & hostname) {return hostName;}
	string & getServerName(string & servername) {return serverName;}
	string & getRealName(string & realname) {return realName;}

	const string& getNickName() {
		return nickName;
	}
};

#endif /* FT_IRC_API_USER */
