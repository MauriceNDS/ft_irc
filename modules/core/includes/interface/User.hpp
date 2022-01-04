#ifndef FT_IRC_USER
#define FT_IRC_USER

#include "ft_irc.hpp"
#include "command/CommandElement.hpp"

class User {
private:
	string name;

public:
	// TODO test
	User(string name) : name(name) {}
};

#endif /* FT_IRC_USER */
