#ifndef FT_IRC_CORE_USER
#define FT_IRC_CORE_USER

#include "ft_irc.hpp"

class User {
private:
	string name;

public:
	// TODO test
	User(string name) : name(name) {}
};

#endif /* FT_IRC_CORE_USER */
