#ifndef FT_IRC_API_USER
#define FT_IRC_API_USER

#include "ft_irc.hpp"

#include "api/Client.hpp"

class User : public Client {
private:
	string nickname;
	string username;
	string realname;
	bool oper;

public:
	// TODO test
	User(Connection *connection) : Client(connection), oper(false) {}

	void setOperator()	{ oper = true; }
	bool isOperator()	{ return oper; }

	void setNickName(const string& nickname)		{ this->nickname = nickname; }
	void setUserName(const string& username)		{ this->username = username; }
	void setRealName(const string& realname)		{ this->realname = realname; }

	const string& getNickName() const				{ return this->nickname; }
	const string& getUserName() const				{ return this->username; }
	const string& getRealName() const				{ return this->realname; }
};

#endif /* FT_IRC_API_USER */
