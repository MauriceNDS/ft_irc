#ifndef FT_IRC_API_USER
#define FT_IRC_API_USER

#include "ft_irc.hpp"

#include "api/Client.hpp"

class User : public Client {
private:
	string nickname;
	string username;
	string realname;

public:
	User(Connection *connection) : Client(connection) {}

	void setNickName(const string& nickname)		{ this->nickname = nickname; }
	void setUserName(const string& username)		{ this->username = username; }
	void setRealName(const string& realname)		{ this->realname = realname; }

	const string& getNickName() const				{ return this->nickname; }
	const string& getUserName() const				{ return this->username; }
	const string& getRealName() const				{ return this->realname; }

	bool isRegistered() const {
		return !getNickName().empty()
			&& !getUserName().empty()
			&& !getRealName().empty();
	}
};

#endif /* FT_IRC_API_USER */
