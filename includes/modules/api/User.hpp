#ifndef FT_IRC_API_USER
#define FT_IRC_API_USER

#include "ft_irc.hpp"

#include "api/Client.hpp"

class User : public Client {
private:
	string name;
	string username;
	string realname;
	bool validPassword;

public:
	User(Connection *connection) : Client(connection) {}

	void setName(const string& name)				{ this->name = name; }
	void setUserName(const string& username)		{ this->username = username; }
	void setRealName(const string& realname)		{ this->realname = realname; }
	void setValidPassword(bool arg)					{ this->validPassword = arg; }

	const string& getName() const					{ return this->name; }
	const string& getUserName() const				{ return this->username; }
	const string& getRealName() const				{ return this->realname; }
	bool getValidPassword() const					{ return this->validPassword; }

	bool isRegistered() const {
		return !getName().empty()
			&& !getUserName().empty()
			&& !getRealName().empty()
			&& getValidPassword();
	}
};

#endif /* FT_IRC_API_USER */
