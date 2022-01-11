#ifndef FT_IRC_API_CHANNEL
#define FT_IRC_API_CHANNEL

#include "ft_irc.hpp"
#include "api/User.hpp"

class Channel {
private:
	string name;
    vector<User *> users;

public:
	// TODO test
	Channel(string name) : name(name) {}

	vector<User *> getUsers() {
		return users;
	}
	
	const string& getName() {
		return name;
	}
};

#endif /* FT_IRC_API_CHANNEL */
