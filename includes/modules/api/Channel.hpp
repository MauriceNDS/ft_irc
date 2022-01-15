#ifndef FT_IRC_API_CHANNEL
#define FT_IRC_API_CHANNEL

#include "ft_irc.hpp"

#include "api/CommandSender.hpp"
#include "api/User.hpp"

class Channel : public CommandSender {
private:
	string name;
    vector<User *> users;

public:
	Channel(string name) : name(name) {}

	vector<User *> getUsers() {
		return users;
	}
	
	const string& getName() {
		return name;
	}

	void send(Response message) const {
		for (vector<User *>::const_iterator it = users.begin(); it != users.end(); it++)
			(*it)->send(message);
	}

	bool isValidIdentifier(const string& identifier) {
		return identifier[0] == '#';
	}
};

#endif /* FT_IRC_API_CHANNEL */
