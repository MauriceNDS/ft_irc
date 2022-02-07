#ifndef FT_IRC_API_USER
#define FT_IRC_API_USER

#include "ft_irc.hpp"

#include "api/Client.hpp"

class User : public Client {
private:
	string nickname;
	string username;
	string realname;
	bool validPassword;

public:
	User(Connection *connection) : Client(connection) {}

	void setNickName(const string& nickname)		{ this->nickname = nickname; }
	void setUserName(const string& username)		{ this->username = username; }
	void setRealName(const string& realname)		{ this->realname = realname; }
	void setValidPassword(bool arg)					{ this->validPassword = arg; }

	const string& getNickName() const				{ return this->nickname; }
	const string& getUserName() const				{ return this->username; }
	const string& getRealName() const				{ return this->realname; }
	bool getValidPassword() const					{ return this->validPassword; }

	const string& getName() const					{ return getNickName(); }

	bool isRegistered() const {
		return !getNickName().empty()
			&& !getUserName().empty()
			&& !getRealName().empty()
			&& getValidPassword();
	}
};

#endif /* FT_IRC_API_USER */
