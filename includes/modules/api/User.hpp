#ifndef FT_IRC_API_USER
#define FT_IRC_API_USER

#include "ft_irc.hpp"

class User {
private:
	string name;

public:
	// TODO test
	User(string name) : name(name) {}

	const string& getName() {
		return name;
	}
};

#endif /* FT_IRC_API_USER */