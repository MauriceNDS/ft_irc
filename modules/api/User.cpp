#include "api/User.hpp"
#include "api/Connection.hpp"

User::User(Connection *connection) : Client(connection) {}

void User::setName(const string& name)				{ this->name = name; }
void User::setUserName(const string& username)		{ this->username = username; }
void User::setRealName(const string& realname)		{ this->realname = realname; }
void User::setValidPassword(bool arg)					{ this->validPassword = arg; }

const string& User::getName() const					{ return this->name; }
const string& User::getUserName() const				{ return this->username; }
const string& User::getRealName() const				{ return this->realname; }

string User::getSenderName() const  {
	return getName() + "@" + getUserName() + "!" + getConnection()->getIP();
}

bool User::isRegistered() const {
	return !getName().empty()
		&& !getUserName().empty()
		&& !getRealName().empty()
		&& getValidPassword();
}

bool User::getValidPassword() const					{ return this->validPassword; }
