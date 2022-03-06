#include "api/User.hpp"
#include "api/Connection.hpp"

User::User(Connection *connection) : Client(connection) {}

void User::setName(const string& name)				{ this->name = name; }
void User::setUserName(const string& username)		{ this->username = username; }
void User::setRealName(const string& realname)		{ this->realname = realname; }
void User::setValidPassword(bool arg)					{ this->validPassword = arg; }

string User::getName() const						{ return this->name; }
const string& User::getUserName() const				{ return this->username; }
const string& User::getRealName() const				{ return this->realname; }

string User::getSenderName() const  {
	return getName() + "!" + getUserName() + "@" + getConnection()->getIP();
}

bool User::isRegistered() const {
	return !getName().empty()
		&& !getUserName().empty()
		&& !getRealName().empty()
		&& getValidPassword();
}

bool User::getValidPassword() const					{ return this->validPassword; }

bool User::isValidName(const string& identifier) {
	string letter = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	string digit = "0123456789";
	string dash = "-";
	string special = "[]\\`_^{|}";

	if (identifier.empty() || identifier.length() > 9)
		return false;
	if ((letter + special).find_first_of(identifier.substr(0, 1)) == std::string::npos)
		return false;
	if ((letter + special + digit + dash).find_first_of(identifier) == std::string::npos)
		return false;
	return true;
}
