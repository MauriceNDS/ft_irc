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
	User(Connection *connection);

	void setName(const string& name);
	void setUserName(const string& username);
	void setRealName(const string& realname);
	void setValidPassword(bool arg);

	string getName() const;
	const string& getUserName() const;
	const string& getRealName() const;
	string getSenderName() const;

	bool isRegistered() const;
	bool getValidPassword() const;

	static bool isValidName(const string& identifier);
};

#endif /* FT_IRC_API_USER */
