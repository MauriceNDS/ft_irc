#ifndef FT_IRC_USER
#define FT_IRC_USER

#include "core.hpp"
#include "command/CommandElement.hpp"

class User {
private:
	string name;

public:
	// TODO test
	User(string name) : name(name) {}
};

// TODO test
User global_user("meuh");

class UserCommandElement : public CommandElement {
public:
	void *parseValue(const string& arg) {
		return &global_user;
	}
};

#endif /* FT_IRC_USER */
