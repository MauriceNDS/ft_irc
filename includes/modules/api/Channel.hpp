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
	Channel(const string& name) : name(name) {}

	const vector<User *>& getUsers() const {
		return users;
	}
	
	const string& getName() const {
		return name;
	}

	void send(const string& message) const {
		for (vector<User *>::const_iterator it = users.begin(); it != users.end(); it++)
			(*it)->send(message);
	}

	static bool isValidIdentifier(const string& identifier) {
		return identifier[0] == '#';
	}
};

#endif /* FT_IRC_API_CHANNEL */
